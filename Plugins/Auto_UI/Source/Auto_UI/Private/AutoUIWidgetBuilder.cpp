// Copyright Epic Games, Inc. All Rights Reserved.

#include "AutoUIWidgetBuilder.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "AutomatedAssetImportData.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Styling/SlateTypes.h"
#include "EditorFramework/AssetImportData.h"
#include "Engine/Texture2D.h"
#include "Engine/Texture.h"
#include "UObject/Package.h"
#include "HAL/FileManager.h"
#include "IAssetTools.h"
#include "ImageCore.h"
#include "ImageUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Misc/FileHelper.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "UObject/SavePackage.h"
#include "WidgetBlueprint.h"
#include "WidgetBlueprintEditorUtils.h"
#include "WidgetBlueprintFactory.h"

#define LOCTEXT_NAMESPACE "AutoUIWidgetBuilder"

namespace AutoUIWidgetBuilder_Private
{
	static FString SanitizeAssetBaseName(FString Raw)
	{
		Raw.TrimStartAndEndInline();
		if (Raw.IsEmpty())
		{
			return TEXT("block");
		}

		FString Out;
		Out.Reserve(Raw.Len());
		for (const TCHAR Ch : Raw)
		{
			if (FChar::IsAlnum(Ch) || Ch == TEXT('_') || Ch == TEXT('-'))
			{
				Out.AppendChar(Ch);
			}
			else
			{
				Out.AppendChar(TEXT('_'));
			}
		}

		while (Out.StartsWith(TEXT("_")))
		{
			Out.RightChopInline(1);
		}

		return Out.IsEmpty() ? TEXT("block") : Out;
	}

	static bool ResolveTextureDirectories(UTexture2D* Texture, FString& OutDiskDir, FString& OutContentPackagePath, FString& OutError)
	{
		OutDiskDir.Reset();
		OutContentPackagePath.Reset();
		OutError.Reset();

		if (!Texture)
		{
			OutError = TEXT("纹理无效。");
			return false;
		}

		OutContentPackagePath = FPackageName::GetLongPackagePath(Texture->GetOutermost()->GetName());
		if (OutContentPackagePath.IsEmpty())
		{
			OutError = TEXT("无法解析纹理 Content 包路径。");
			return false;
		}

		if (Texture->AssetImportData)
		{
			const FString SourceFile = Texture->AssetImportData->GetFirstFilename();
			if (!SourceFile.IsEmpty())
			{
				OutDiskDir = FPaths::GetPath(SourceFile);
				return true;
			}
		}

		FString PackageFilename;
		if (FPackageName::TryConvertLongPackageNameToFilename(
				Texture->GetOutermost()->GetName(),
				PackageFilename,
				FPackageName::GetAssetPackageExtension()))
		{
			OutDiskDir = FPaths::GetPath(PackageFilename);
			return true;
		}

		OutError = TEXT("无法解析源纹理目录（缺少导入路径且无法定位 .uasset）。");
		return false;
	}

	static bool CropBgraRect(
		const TArray<uint8>& Src,
		const int32 SrcW,
		const int32 SrcH,
		const FAutoUILayoutIconEntry& Block,
		TArray<uint8>& OutBgra,
		int32& OutW,
		int32& OutH)
	{
		OutBgra.Reset();
		OutW = 0;
		OutH = 0;

		if (SrcW <= 0 || SrcH <= 0 || Block.W <= 0 || Block.H <= 0)
		{
			return false;
		}

		const int32 X0 = FMath::Clamp(Block.X, 0, SrcW - 1);
		const int32 Y0 = FMath::Clamp(Block.Y, 0, SrcH - 1);
		const int32 X1 = FMath::Clamp(Block.X + Block.W, X0 + 1, SrcW);
		const int32 Y1 = FMath::Clamp(Block.Y + Block.H, Y0 + 1, SrcH);

		OutW = X1 - X0;
		OutH = Y1 - Y0;
		OutBgra.SetNumZeroed(OutW * OutH * 4);

		for (int32 Row = 0; Row < OutH; ++Row)
		{
			const int32 SrcRow = Y0 + Row;
			const int32 SrcOffset = (SrcRow * SrcW + X0) * 4;
			const int32 DstOffset = Row * OutW * 4;
			FMemory::Memcpy(OutBgra.GetData() + DstOffset, Src.GetData() + SrcOffset, static_cast<SIZE_T>(OutW) * 4);
		}

		return true;
	}

	static bool SavePngToDisk(const TArray<uint8>& Bgra, const int32 W, const int32 H, const FString& FilePath, FString& OutError)
	{
		FImage Image;
		Image.Init(W, H, ERawImageFormat::BGRA8, EGammaSpace::Linear);
		if (Image.RawData.Num() < Bgra.Num())
		{
			OutError = TEXT("图像缓冲不足。");
			return false;
		}

		FMemory::Memcpy(Image.RawData.GetData(), Bgra.GetData(), Bgra.Num());

		TArray64<uint8> PngBytes64;
		if (!FImageUtils::CompressImage(PngBytes64, TEXT("png"), Image) || PngBytes64.Num() == 0)
		{
			OutError = TEXT("PNG 压缩失败。");
			return false;
		}

		TArray<uint8> PngBytes;
		PngBytes.Append(PngBytes64.GetData(), static_cast<int32>(PngBytes64.Num()));

		if (!FFileHelper::SaveArrayToFile(PngBytes, *FilePath))
		{
			OutError = FString::Printf(TEXT("写入失败：%s"), *FilePath);
			return false;
		}

		return true;
	}

	static UTexture2D* ImportPngToContent(const FString& PngPath, const FString& DestinationPath, const FString& AssetName, FString& OutError)
	{
		UAutomatedAssetImportData* ImportData = NewObject<UAutomatedAssetImportData>(GetTransientPackage());
		ImportData->DestinationPath = DestinationPath;
		ImportData->Filenames.Add(PngPath);
		ImportData->bReplaceExisting = true;
		ImportData->FactoryName = TEXT("TextureFactory");

		FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));
		const TArray<UObject*> Imported = AssetToolsModule.Get().ImportAssetsAutomated(ImportData);
		for (UObject* Obj : Imported)
		{
			if (UTexture2D* Tex = Cast<UTexture2D>(Obj))
			{
				return Tex;
			}
		}

		const FString ObjectPath = FString::Printf(TEXT("%s/%s.%s"), *DestinationPath, *AssetName, *AssetName);
		if (UTexture2D* Existing = LoadObject<UTexture2D>(nullptr, *ObjectPath))
		{
			return Existing;
		}

		OutError = FString::Printf(TEXT("导入失败：%s"), *PngPath);
		return nullptr;
	}

	struct FExportedBlock
	{
		FAutoUILayoutIconEntry Block;
		FString AssetName;
		TObjectPtr<UTexture2D> Texture = nullptr;
	};

	enum class EAutoUIWidgetKind : uint8
	{
		Image,
		Button,
	};

	/** image / panel / text / 空 / 未知 → Image；button → Button。 */
	static EAutoUIWidgetKind ResolveWidgetKind(const FString& WidgetType)
	{
		if (WidgetType.Equals(TEXT("button"), ESearchCase::IgnoreCase))
		{
			return EAutoUIWidgetKind::Button;
		}
		return EAutoUIWidgetKind::Image;
	}

	static void RegisterWidgetVariable(UWidgetBlueprint* WidgetBP, const FName WidgetName)
	{
		if (WidgetBP && !WidgetBP->WidgetVariableNameToGuidMap.Contains(WidgetName))
		{
			WidgetBP->OnVariableAdded(WidgetName);
		}
	}

	static void ApplyTextureAsButtonBackground(UButton* Button, UTexture2D* Texture)
	{
		if (!Button || !Texture)
		{
			return;
		}

		const FVector2D ImageSize(
			static_cast<float>(FMath::Max(1, Texture->GetSizeX())),
			static_cast<float>(FMath::Max(1, Texture->GetSizeY())));

		FButtonStyle Style = Button->GetStyle();
		auto SetBrush = [Texture, ImageSize](FSlateBrush& Brush)
		{
			Brush.SetResourceObject(Texture);
			Brush.ImageSize = ImageSize;
			Brush.DrawAs = ESlateBrushDrawType::Image;
			Brush.Tiling = ESlateBrushTileType::NoTile;
		};

		SetBrush(Style.Normal);
		SetBrush(Style.Hovered);
		SetBrush(Style.Pressed);
		SetBrush(Style.Disabled);
		Button->SetStyle(Style);
		Button->SetBackgroundColor(FLinearColor::White);
	}

	static UWidget* CreateTypedChildWidget(
		UWidgetBlueprint* WidgetBP,
		const FExportedBlock& Exported,
		const EAutoUIWidgetKind Kind,
		FName& OutWidgetName)
	{
		if (!WidgetBP || !WidgetBP->WidgetTree || !Exported.Texture)
		{
			return nullptr;
		}

		if (Kind == EAutoUIWidgetKind::Button)
		{
			OutWidgetName = FName(*FString::Printf(TEXT("Btn_%s"), *Exported.AssetName));
			UButton* ButtonWidget = WidgetBP->WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), OutWidgetName);
			RegisterWidgetVariable(WidgetBP, OutWidgetName);
			ApplyTextureAsButtonBackground(ButtonWidget, Exported.Texture);
			return ButtonWidget;
		}

		OutWidgetName = FName(*FString::Printf(TEXT("Img_%s"), *Exported.AssetName));
		UImage* ImageWidget = WidgetBP->WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), OutWidgetName);
		RegisterWidgetVariable(WidgetBP, OutWidgetName);
		ImageWidget->SetBrushFromTexture(Exported.Texture, false);
		return ImageWidget;
	}

	static UCanvasPanel* EnsureRootCanvas(UWidgetBlueprint* WidgetBP)
	{
		if (!WidgetBP || !WidgetBP->WidgetTree)
		{
			return nullptr;
		}

		if (UCanvasPanel* Existing = Cast<UCanvasPanel>(WidgetBP->WidgetTree->RootWidget))
		{
			return Existing;
		}

		WidgetBP->WidgetTree->Modify();
		WidgetBP->Modify();
		if (UWidget* OldRoot = WidgetBP->WidgetTree->RootWidget)
		{
			const FName OldRootName = OldRoot->GetFName();
			WidgetBP->WidgetTree->RemoveWidget(OldRoot);
			if (WidgetBP->WidgetVariableNameToGuidMap.Contains(OldRootName))
			{
				WidgetBP->OnVariableRemoved(OldRootName);
			}
			OldRoot->Rename(nullptr, GetTransientPackage());
		}

		UCanvasPanel* Canvas = WidgetBP->WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootCanvas"));
		WidgetBP->WidgetTree->RootWidget = Canvas;
		if (!WidgetBP->WidgetVariableNameToGuidMap.Contains(Canvas->GetFName()))
		{
			WidgetBP->OnVariableAdded(Canvas->GetFName());
		}
		return Canvas;
	}

	static void ClearCanvasChildren(UWidgetBlueprint* WidgetBP, UCanvasPanel* Canvas)
	{
		if (!WidgetBP || !Canvas)
		{
			return;
		}

		TSet<UWidget*> ToDelete;
		for (UWidget* Child : Canvas->GetAllChildren())
		{
			if (Child)
			{
				ToDelete.Add(Child);
			}
		}

		if (ToDelete.Num() > 0)
		{
			FWidgetBlueprintEditorUtils::DeleteWidgets(
				WidgetBP,
				ToDelete,
				FWidgetBlueprintEditorUtils::EDeleteWidgetWarningType::DeleteSilently);
		}
	}

	static void ApplyAnchorSlot(
		UCanvasPanelSlot* Slot,
		const FAutoUILayoutIconEntry& Block,
		const FIntPoint DesignSize)
	{
		if (!Slot || DesignSize.X <= 0 || DesignSize.Y <= 0)
		{
			return;
		}

		const float DW = static_cast<float>(DesignSize.X);
		const float DH = static_cast<float>(DesignSize.Y);

		FAnchorData Layout;
		Layout.Alignment = FVector2D::ZeroVector;
		Layout.Offsets = FMargin(0.f);
		Layout.Anchors.Minimum = FVector2D(
			static_cast<float>(Block.X) / DW,
			static_cast<float>(Block.Y) / DH);
		Layout.Anchors.Maximum = FVector2D(
			static_cast<float>(Block.X + Block.W) / DW,
			static_cast<float>(Block.Y + Block.H) / DH);

		Slot->SetLayout(Layout);
		Slot->SetAutoSize(false);
		Slot->SetZOrder(Block.ZOrder);
	}

	static UWidgetBlueprint* CreateOrLoadWidgetBlueprint(const FString& PackagePath, const FString& AssetName, FString& OutError)
	{
		const FString FullPath = PackagePath / AssetName;
		if (UWidgetBlueprint* Existing = LoadObject<UWidgetBlueprint>(nullptr, *(FullPath + TEXT(".") + AssetName)))
		{
			return Existing;
		}

		UPackage* Package = CreatePackage(*(FullPath));
		if (!Package)
		{
			OutError = FString::Printf(TEXT("无法创建包：%s"), *FullPath);
			return nullptr;
		}

		UWidgetBlueprintFactory* Factory = NewObject<UWidgetBlueprintFactory>();
		Factory->ParentClass = UUserWidget::StaticClass();

		UWidgetBlueprint* WidgetBP = Cast<UWidgetBlueprint>(
			Factory->FactoryCreateNew(
				UWidgetBlueprint::StaticClass(),
				Package,
				FName(*AssetName),
				RF_Public | RF_Standalone,
				nullptr,
				GWarn));

		if (!WidgetBP)
		{
			OutError = FString::Printf(TEXT("创建 WidgetBlueprint 失败：%s"), *FullPath);
			return nullptr;
		}

		FAssetRegistryModule::AssetCreated(WidgetBP);
		Package->MarkPackageDirty();
		return WidgetBP;
	}

	static bool SaveBlueprintPackage(UWidgetBlueprint* WidgetBP, FString& OutError)
	{
		if (!WidgetBP)
		{
			OutError = TEXT("WidgetBlueprint 无效。");
			return false;
		}

		WidgetBP->Modify();
		WidgetBP->MarkPackageDirty();

		FKismetEditorUtilities::CompileBlueprint(WidgetBP);

		UPackage* Package = WidgetBP->GetOutermost();
		const FString PackageFileName = FPackageName::LongPackageNameToFilename(
			Package->GetName(),
			FPackageName::GetAssetPackageExtension());

		FSavePackageArgs SaveArgs;
		SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
		if (!UPackage::SavePackage(Package, WidgetBP, *PackageFileName, SaveArgs))
		{
			OutError = FString::Printf(TEXT("保存 WidgetBlueprint 失败：%s"), *PackageFileName);
			return false;
		}

		return true;
	}
}

FAutoUIBuildWidgetResult AutoUI_BuildWidgetFromLayout(
	UTexture2D* SourceTexture,
	const FAutoUILayoutSpec& LayoutSpec,
	const TArray<uint8>& CropBgra,
	const int32 CropWidth,
	const int32 CropHeight)
{
	using namespace AutoUIWidgetBuilder_Private;

	FAutoUIBuildWidgetResult Result;

	if (!SourceTexture)
	{
		Result.Error = TEXT("未选择布局纹理。");
		return Result;
	}

	if (LayoutSpec.Icons.Num() == 0)
	{
		Result.Error = TEXT("布局中没有分块（blocks/icons）。");
		return Result;
	}

	if (CropBgra.Num() == 0 || CropWidth <= 0 || CropHeight <= 0)
	{
		Result.Error = TEXT("裁切源像素无效。");
		return Result;
	}

	if (LayoutSpec.DesignSize.X <= 0 || LayoutSpec.DesignSize.Y <= 0)
	{
		Result.Error = TEXT("design_size 无效。");
		return Result;
	}

	FString DirError;
	if (!ResolveTextureDirectories(SourceTexture, Result.SourceTextureDir, Result.SubTexContentPath, DirError))
	{
		Result.Error = DirError;
		return Result;
	}

	Result.SubTexDiskDir = FPaths::Combine(Result.SourceTextureDir, TEXT("sub_Tex"));
	Result.SubTexContentPath = Result.SubTexContentPath / TEXT("sub_Tex");

	if (!IFileManager::Get().MakeDirectory(*Result.SubTexDiskDir, true))
	{
		Result.Error = FString::Printf(TEXT("无法创建目录：%s"), *Result.SubTexDiskDir);
		return Result;
	}

	TArray<AutoUIWidgetBuilder_Private::FExportedBlock> ExportedBlocks;
	TSet<FString> UsedAssetNames;

	for (const FAutoUILayoutIconEntry& Block : LayoutSpec.Icons)
	{
		TArray<uint8> BlockBgra;
		int32 BlockW = 0;
		int32 BlockH = 0;
		if (!CropBgraRect(CropBgra, CropWidth, CropHeight, Block, BlockBgra, BlockW, BlockH))
		{
			continue;
		}

		const FString BaseName = SanitizeAssetBaseName(Block.Id);
		FString UniqueName = BaseName;
		int32 Suffix = 1;
		while (UsedAssetNames.Contains(UniqueName))
		{
			UniqueName = FString::Printf(TEXT("%s_%d"), *BaseName, Suffix++);
		}
		UsedAssetNames.Add(UniqueName);

		const FString PngPath = FPaths::Combine(Result.SubTexDiskDir, UniqueName + TEXT(".png"));
		FString SaveErr;
		if (!SavePngToDisk(BlockBgra, BlockW, BlockH, PngPath, SaveErr))
		{
			Result.Error = SaveErr;
			return Result;
		}

		++Result.BlocksExported;

		FString ImportErr;
		UTexture2D* Imported = ImportPngToContent(PngPath, Result.SubTexContentPath, UniqueName, ImportErr);
		if (!Imported)
		{
			Result.Error = ImportErr;
			return Result;
		}

		AutoUIWidgetBuilder_Private::FExportedBlock Record;
		Record.Block = Block;
		Record.AssetName = UniqueName;
		Record.Texture = Imported;
		ExportedBlocks.Add(MoveTemp(Record));
		++Result.TexturesImported;
	}

	if (Result.BlocksExported == 0)
	{
		Result.Error = TEXT("没有成功导出任何分块（请检查 rect 是否在图像范围内）。");
		return Result;
	}

	const FString TextureAssetName = SourceTexture->GetName();
	const FString WbpName = FString::Printf(TEXT("WBP_%s_AutoUI"), *TextureAssetName);
	const FString WbpPackagePath = FPackageName::GetLongPackagePath(SourceTexture->GetOutermost()->GetName());

	FString WbpError;
	UWidgetBlueprint* WidgetBP = CreateOrLoadWidgetBlueprint(WbpPackagePath, WbpName, WbpError);
	if (!WidgetBP)
	{
		Result.Error = WbpError;
		return Result;
	}

	UCanvasPanel* RootCanvas = EnsureRootCanvas(WidgetBP);
	if (!RootCanvas)
	{
		Result.Error = TEXT("无法创建根 CanvasPanel。");
		return Result;
	}

	WidgetBP->WidgetTree->Modify();
	WidgetBP->Modify();
	ClearCanvasChildren(WidgetBP, RootCanvas);

	const FIntPoint DesignSize = LayoutSpec.DesignSize;

	for (const FExportedBlock& Exported : ExportedBlocks)
	{
		if (!Exported.Texture)
		{
			continue;
		}

		const EAutoUIWidgetKind Kind = ResolveWidgetKind(Exported.Block.WidgetType);
		FName WidgetName;
		UWidget* ChildWidget = CreateTypedChildWidget(WidgetBP, Exported, Kind, WidgetName);
		if (!ChildWidget)
		{
			continue;
		}

		UCanvasPanelSlot* Slot = RootCanvas->AddChildToCanvas(ChildWidget);
		ApplyAnchorSlot(Slot, Exported.Block, DesignSize);
	}

	FString SaveErr;
	if (!SaveBlueprintPackage(WidgetBP, SaveErr))
	{
		Result.Error = SaveErr;
		return Result;
	}

	Result.WidgetBlueprintPath = WbpPackagePath / WbpName;
	Result.bSuccess = true;
	return Result;
}

#undef LOCTEXT_NAMESPACE
