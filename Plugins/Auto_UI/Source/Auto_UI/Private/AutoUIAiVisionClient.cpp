// Copyright Epic Games, Inc. All Rights Reserved.

#include "AutoUIAiVisionClient.h"

#include "AutoUIAiServiceSettings.h"
#include "AutoUILayoutJson.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Engine/Texture2D.h"
#include "HttpModule.h"
#include "ImageCore.h"
#include "ImageUtils.h"
#include "Interfaces/IHttpBase.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformMisc.h"
#include "HAL/PlatformProcess.h"
#include "Misc/Base64.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/ScopeExit.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Async/Async.h"

namespace AutoUIAiVision_Private
{
	static FString StripMarkdownJsonFences(FString In);

	static FString QuoteProcessArgument(const FString& Value)
	{
		return TEXT("\"") + Value.Replace(TEXT("\""), TEXT("\\\"")) + TEXT("\"");
	}

	static FString ResolveCodexExecutable()
	{
		TArray<FString> Candidates;

		const FString LocalAppData = FPlatformMisc::GetEnvironmentVariable(TEXT("LOCALAPPDATA"));
		if (!LocalAppData.IsEmpty())
		{
			const FString WindowsApps = FPaths::Combine(LocalAppData, TEXT("Microsoft/WindowsApps/codex.exe"));
			Candidates.Add(WindowsApps);
		}

		const FString AppData = FPlatformMisc::GetEnvironmentVariable(TEXT("APPDATA"));
		if (!AppData.IsEmpty())
		{
			Candidates.Add(FPaths::Combine(
				AppData,
				TEXT("npm/node_modules/@openai/codex/node_modules/@openai/codex-win32-x64/vendor/x86_64-pc-windows-msvc/bin/codex.exe")));
		}

		for (const FString& Candidate : Candidates)
		{
			if (FPaths::FileExists(Candidate))
			{
				return FPaths::ConvertRelativePathToFull(Candidate);
			}
		}
		Candidates.Reset();

		const FString ProgramFiles = FPlatformMisc::GetEnvironmentVariable(TEXT("ProgramFiles"));
		if (!ProgramFiles.IsEmpty())
		{
			const FString WindowsAppsRoot = FPaths::Combine(ProgramFiles, TEXT("WindowsApps"));
				TArray<FString> AppPackages;
				IFileManager::Get().FindFiles(AppPackages, *FPaths::Combine(WindowsAppsRoot, TEXT("OpenAI.Codex_*_x64__*")), false, true);
			AppPackages.Sort([](const FString& A, const FString& B) { return A > B; });
			for (const FString& Package : AppPackages)
			{
				Candidates.Add(FPaths::Combine(WindowsAppsRoot, Package, TEXT("app/resources/codex.exe")));
			}
		}

		for (const FString& Candidate : Candidates)
		{
			if (FPaths::FileExists(Candidate))
			{
				return FPaths::ConvertRelativePathToFull(Candidate);
			}
		}

		// CreateProcess can resolve codex.exe from PATH when Unreal inherited the CLI path.
		return TEXT("codex.exe");
	}

	static bool ShouldUseCodexCli()
	{
		const FString ForceRest = FPlatformMisc::GetEnvironmentVariable(TEXT("AUTO_UI_USE_REST")).TrimStartAndEnd();
		return !(ForceRest == TEXT("1") || ForceRest.Equals(TEXT("true"), ESearchCase::IgnoreCase));
	}

	static bool ParseAndValidateLayoutJson(
		const FString& RawOutput,
		const FString& ImageSourceLabel,
		FString& OutMessage,
		TOptional<FAutoUILayoutSpec>& OutSpec)
	{
		const FString LayoutJson = StripMarkdownJsonFences(RawOutput);
		FAutoUILayoutSpec Spec;
		TArray<FString> ValErrors;
		const bool bOk = AutoUI_ParseAndValidateLayoutJson(
			LayoutJson,
			Spec,
			ValErrors,
			EAutoUILayoutJsonValidation::EditorPreview);

		if (!bOk || Spec.Icons.Num() == 0)
		{
			OutMessage = TEXT("模型返回的 JSON 无法用于预览（解析/校验失败）：\n");
			for (const FString& Error : ValErrors)
			{
				OutMessage += Error + TEXT("\n");
			}
			OutMessage += TEXT("\n--- 模型输出（截断）---\n");
			OutMessage += LayoutJson.Left(4000);
			return false;
		}

		OutMessage = FString::Printf(
			TEXT("AI 分析完成（识图输入：%s），已在预览上标出 %d 个分块。\n"),
			*ImageSourceLabel,
			Spec.Icons.Num());
		if (ValErrors.Num() > 0)
		{
			OutMessage += TEXT("\n注意：\n");
			for (const FString& Error : ValErrors)
			{
				OutMessage += Error + TEXT("\n");
			}
		}
		OutMessage += TEXT("\n--- JSON（可复制保存）---\n");
		OutMessage += LayoutJson;
		OutSpec = TOptional<FAutoUILayoutSpec>(MoveTemp(Spec));
		return true;
	}

	/** 若用户只填了 …/v1 根路径，则补全为 OpenAI 兼容的 chat/completions。 */
	static FString NormalizeServiceUrl(FString Url)
	{
		Url.TrimStartAndEndInline();
		if (Url.IsEmpty())
		{
			return Url;
		}
		if (!Url.Contains(TEXT("chat/completions"), ESearchCase::IgnoreCase))
		{
			while (Url.EndsWith(TEXT("/")))
			{
				Url.LeftChopInline(1, EAllowShrinking::No);
			}
			if (Url.EndsWith(TEXT("/v1"), ESearchCase::IgnoreCase))
			{
				Url += TEXT("/chat/completions");
			}
		}
		return Url;
	}

	static FString StripMarkdownJsonFences(FString In)
	{
		FString S = In.TrimStartAndEnd();
		if (S.StartsWith(TEXT("```")))
		{
			const int32 FirstNl = S.Find(TEXT("\n"));
			if (FirstNl != INDEX_NONE)
			{
				S = S.Mid(FirstNl + 1);
			}
			const int32 Fence = S.Find(TEXT("```"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
			if (Fence != INDEX_NONE)
			{
				S = S.Left(Fence);
			}
		}
		return S.TrimStartAndEnd();
	}

	static bool TryExtractLayoutJsonFromChatResponse(const FString& ResponseBody, FString& OutLayoutJson, FString& OutError)
	{
		TSharedPtr<FJsonValue> RootVal;
		const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);
		if (!FJsonSerializer::Deserialize(Reader, RootVal) || !RootVal.IsValid())
		{
			OutError = TEXT("无法解析 HTTP 响应为 JSON。");
			return false;
		}

		const TSharedPtr<FJsonObject>* RootObjPtr = nullptr;
		if (!RootVal->TryGetObject(RootObjPtr) || RootObjPtr == nullptr || !RootObjPtr->IsValid())
		{
			OutError = TEXT("根节点不是对象。");
			return false;
		}
		const TSharedPtr<FJsonObject>& RootObj = *RootObjPtr;

		const TArray<TSharedPtr<FJsonValue>>* Choices = nullptr;
		if (RootObj->TryGetArrayField(TEXT("choices"), Choices) && Choices && Choices->Num() > 0)
		{
			const TSharedPtr<FJsonObject>* Choice0Ptr = nullptr;
			if (!(*Choices)[0]->TryGetObject(Choice0Ptr) || Choice0Ptr == nullptr || !Choice0Ptr->IsValid())
			{
				OutError = TEXT("choices[0] 不是对象。");
				return false;
			}
			const TSharedPtr<FJsonObject>& Choice0 = *Choice0Ptr;

			const TSharedPtr<FJsonObject>* MsgPtr = nullptr;
			if (!Choice0->TryGetObjectField(TEXT("message"), MsgPtr) || MsgPtr == nullptr || !MsgPtr->IsValid())
			{
				OutError = TEXT("缺少 message 对象。");
				return false;
			}
			const TSharedPtr<FJsonObject>& Msg = *MsgPtr;

			FString ContentStr;
			if (!Msg->TryGetStringField(TEXT("content"), ContentStr))
			{
				OutError = TEXT("message.content 不是字符串。");
				return false;
			}

			OutLayoutJson = StripMarkdownJsonFences(ContentStr);
			return true;
		}

		if (RootObj->HasField(TEXT("schema_version")))
		{
			OutLayoutJson = ResponseBody;
			return true;
		}

		OutError = TEXT("响应中未找到 choices，且根对象也不是布局 JSON。");
		return false;
	}

	static FString BuildUserPrompt(int32 W, int32 H)
	{
		return FString::Printf(
			TEXT("你是 UI 布局分析助手。请分析附带的全屏 UI 效果图（常为透明底 PNG），按「语义上的独立 UI 分块」输出列表。\n")
			TEXT("分块含义：用户一眼能区分的功能区/面板/条带，例如：顶栏标题胶囊、每条侧边导航行（图标+文字视为同一块）、中间主内容大面板等。\n")
			TEXT("硬性规则：若两块区域的前景像素在图像上 8-连通相连（仅隔透明像素可视为不连），必须合并为一块 rect，禁止拆成两项。\n")
			TEXT("彼此在画面上分离、中间为透明/背景的（如左右两个独立状态条）才可分成两块。同一按钮行内图文不得拆开。\n")
			TEXT("只输出一个 JSON 对象：合法 JSON；禁止 Markdown 代码块、禁止注释、禁止在 JSON 前后输出任何说明文字。\n")
			TEXT("design_size 必须与图像像素尺寸完全一致：w=%d, h=%d（不得改分辨率或缩放坐标）。\n")
			TEXT("分块拆分规则（必须严格遵守）：\n")
			TEXT("- 每个 blocks[]（或 icons[]）元素 = 一个 UI 分块；为该分块整体画一个轴对齐最小外接矩形 rect，包住该区域内所有可见 UI（描边、发光、文字、小图标都算在该块内）。\n")
			TEXT("- 禁止把同一连通前景区域拆成多个 rect；禁止把同一按钮条里的图文拆成多项。\n")
			TEXT("坐标与 rect（必须严格遵守，与下游程序一致）：\n")
			TEXT("- 全图使用屏幕式像素坐标：原点在图像左上角 (0,0)；x 向右增大，y 向下增大。\n")
			TEXT("- 每项 rect 的 (x,y) 必须是该分块外接矩形的左上角像素坐标（定位枢轴 pivot 固定在左上角）；(w,h) 为宽高（像素，正整数）。\n")
			TEXT("- rect 必须完全落在 design_size 内：x>=0，y>=0，x+w<=设计宽度，y+h<=设计高度；不要用浮点数。\n")
			TEXT("- 若你用归一化思考：UV 原点同样在左上角；但最终只输出像素 rect，不要添加未约定的额外字段。\n")
			TEXT("字段：schema_version 固定为 1；version 为正整数（无把握可写 1）；用 blocks 数组存放分块列表（每项必须含 id、rect、widget_type、z_order）；亦可用 icons 作为同义字段名，二者择一即可。\n")
			TEXT("id：仅用英文字母、数字、下划线与连字符，全局唯一、语义化；不得重复。\n")
			TEXT("widget_type：\"panel\"（大面板/主内容区）、\"button\"（可点击条/按钮行）、\"text\"（以文字为主的信息条）、\"image\"（装饰性图块）；不确定时用 panel 或 image。\n")
			TEXT("z_order：整数叠放顺序，数值更大表示更靠近用户、应盖住更小的（同一图内保持自洽）。\n")
			TEXT("格式必须满足：\n")
			TEXT("{\n")
			TEXT("  \"schema_version\": 1,\n")
			TEXT("  \"version\": 1,\n")
			TEXT("  \"design_size\": { \"w\": %d, \"h\": %d },\n")
			TEXT("  \"blocks\": [\n")
			TEXT("    { \"id\": \"唯一英文id\", \"rect\": { \"x\": 整数, \"y\": 整数, \"w\": 整数, \"h\": 整数 }, \"widget_type\": \"panel|button|text|image\", \"z_order\": 整数 }\n")
			TEXT("  ]\n")
			TEXT("}\n"),
			W,
			H,
			W,
			H);
	}

	static void RequestLayoutJsonViaCodex(
		const TArray<uint8>& PngBytes,
		const int32 ImageWidth,
		const int32 ImageHeight,
		const FString& ImageSourceLabel,
		TFunction<void(bool bOk, FString Message, TOptional<FAutoUILayoutSpec> Spec)> OnCompleteOnGameThread)
	{
		Async(EAsyncExecution::ThreadPool,
			[PngBytes, ImageWidth, ImageHeight, ImageSourceLabel, OnCompleteOnGameThread = MoveTemp(OnCompleteOnGameThread)]() mutable
			{
				auto Finish = [OnCompleteOnGameThread](bool bOk, FString Message, TOptional<FAutoUILayoutSpec> Spec = TOptional<FAutoUILayoutSpec>()) mutable
				{
					AsyncTask(ENamedThreads::GameThread,
						[OnCompleteOnGameThread = MoveTemp(OnCompleteOnGameThread), bOk, Message = MoveTemp(Message), Spec = MoveTemp(Spec)]() mutable
						{
							OnCompleteOnGameThread(bOk, MoveTemp(Message), MoveTemp(Spec));
						});
				};

				const FString TempDir = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectIntermediateDir(), TEXT("AutoUI")));
				if (!IFileManager::Get().MakeDirectory(*TempDir, true))
				{
					Finish(false, TEXT("无法创建 Auto UI 的临时目录。"));
					return;
				}

				const FString Token = FGuid::NewGuid().ToString(EGuidFormats::Digits);
				const FString ImagePath = FPaths::Combine(TempDir, Token + TEXT(".png"));
				const FString InstructionPath = FPaths::Combine(TempDir, Token + TEXT(".txt"));
				const FString OutputPath = FPaths::Combine(TempDir, Token + TEXT(".json"));
				ON_SCOPE_EXIT
				{
					IFileManager::Get().Delete(*ImagePath, false, true);
					IFileManager::Get().Delete(*InstructionPath, false, true);
					IFileManager::Get().Delete(*OutputPath, false, true);
				};

				const FString Instructions = BuildUserPrompt(ImageWidth, ImageHeight);
				if (!FFileHelper::SaveArrayToFile(PngBytes, *ImagePath)
					|| !FFileHelper::SaveStringToFile(Instructions, *InstructionPath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
				{
					Finish(false, TEXT("无法写入 Codex 分析所需的临时文件。"));
					return;
				}

				FString CodexExecutable = FPlatformMisc::GetEnvironmentVariable(TEXT("AUTO_UI_CODEX_PATH"));
				CodexExecutable.TrimStartAndEndInline();
				if (CodexExecutable.IsEmpty())
				{
					CodexExecutable = ResolveCodexExecutable();
				}

				const FString CliPrompt = FString::Printf(
					TEXT("Read the instructions from %s and follow them exactly for the attached image. Return only the requested JSON object."),
					*InstructionPath);
				const FString Params = FString::Printf(
					TEXT("exec --ephemeral --ignore-user-config --ignore-rules --skip-git-repo-check --sandbox read-only --color never -C %s -i %s -o %s %s"),
					*QuoteProcessArgument(TempDir),
					*QuoteProcessArgument(ImagePath),
					*QuoteProcessArgument(OutputPath),
					*QuoteProcessArgument(CliPrompt));

				int32 ReturnCode = INDEX_NONE;
				FString StdOut;
				FString StdErr;
				const bool bStarted = FPlatformProcess::ExecProcess(
					*CodexExecutable,
					*Params,
					&ReturnCode,
					&StdOut,
					&StdErr,
					*TempDir,
					true);

				if (!bStarted || ReturnCode != 0)
				{
					FString Detail = StdErr.TrimStartAndEnd();
					if (Detail.IsEmpty())
					{
						Detail = StdOut.TrimStartAndEnd();
					}
					Finish(false, FString::Printf(
						TEXT("无法调用本机 Codex CLI（返回码 %d）。请先在 Terminal 中运行 `codex login status`；也可在设置中关闭自动模式，改用 REST。\n%s"),
						ReturnCode,
						*Detail.Left(2000)));
					return;
				}

				FString RawOutput;
				if (!FFileHelper::LoadFileToString(RawOutput, *OutputPath) || RawOutput.TrimStartAndEnd().IsEmpty())
				{
					Finish(false, TEXT("Codex CLI 已结束，但没有返回布局 JSON。"));
					return;
				}

				FString Message;
				TOptional<FAutoUILayoutSpec> Spec;
				const bool bOk = ParseAndValidateLayoutJson(RawOutput, ImageSourceLabel + TEXT(" / Codex CLI"), Message, Spec);
				Finish(bOk, MoveTemp(Message), MoveTemp(Spec));
			});
	}

	static FString BuildRequestJson(const FString& ModelName, const FString& Base64Png, int32 W, int32 H)
	{
		const FString DataUrl = FString::Printf(TEXT("data:image/png;base64,%s"), *Base64Png);
		const FString Prompt = BuildUserPrompt(W, H);

		const TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
		Root->SetStringField(TEXT("model"), ModelName);

		TArray<TSharedPtr<FJsonValue>> Messages;
		const TSharedPtr<FJsonObject> UserMsg = MakeShared<FJsonObject>();
		UserMsg->SetStringField(TEXT("role"), TEXT("user"));

		TArray<TSharedPtr<FJsonValue>> Content;

		const TSharedPtr<FJsonObject> TextPart = MakeShared<FJsonObject>();
		TextPart->SetStringField(TEXT("type"), TEXT("text"));
		TextPart->SetStringField(TEXT("text"), Prompt);
		Content.Add(MakeShared<FJsonValueObject>(TextPart));

		const TSharedPtr<FJsonObject> ImgPart = MakeShared<FJsonObject>();
		ImgPart->SetStringField(TEXT("type"), TEXT("image_url"));
		const TSharedPtr<FJsonObject> ImgUrlObj = MakeShared<FJsonObject>();
		ImgUrlObj->SetStringField(TEXT("url"), DataUrl);
		ImgPart->SetObjectField(TEXT("image_url"), ImgUrlObj);
		Content.Add(MakeShared<FJsonValueObject>(ImgPart));

		UserMsg->SetArrayField(TEXT("content"), Content);
		Messages.Add(MakeShared<FJsonValueObject>(UserMsg));
		Root->SetArrayField(TEXT("messages"), Messages);

		FString Out;
		const TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Out);
		FJsonSerializer::Serialize(Root.ToSharedRef(), Writer);
		return Out;
	}

	static void RequestLayoutJsonFromPngInternal(
		const TArray<uint8>& PngBytes,
		const int32 ImageWidth,
		const int32 ImageHeight,
		const FString& ImageSourceLabel,
		TFunction<void(bool bOk, FString Message, TOptional<FAutoUILayoutSpec> Spec)> OnCompleteOnGameThread)
	{
		if (!OnCompleteOnGameThread)
		{
			return;
		}

		if (PngBytes.Num() == 0 || ImageWidth <= 0 || ImageHeight <= 0)
		{
			OnCompleteOnGameThread(false, TEXT("PNG 图像数据无效。"), TOptional<FAutoUILayoutSpec>());
			return;
		}

		const UAutoUIAiServiceSettings* Settings = GetDefault<UAutoUIAiServiceSettings>();
		if (ShouldUseCodexCli())
		{
			RequestLayoutJsonViaCodex(
				PngBytes,
				ImageWidth,
				ImageHeight,
				ImageSourceLabel,
				MoveTemp(OnCompleteOnGameThread));
			return;
		}

		const FString Url = AutoUIAiVision_Private::NormalizeServiceUrl(Settings->ServiceUrl);
		const FString Model = Settings->ModelName.TrimStartAndEnd();
		FString ApiKey = Settings->ApiKey.TrimStartAndEnd();
		if (ApiKey.IsEmpty())
		{
			ApiKey = FPlatformMisc::GetEnvironmentVariable(TEXT("OPENAI_API_KEY")).TrimStartAndEnd();
		}

		if (Url.IsEmpty() || Model.IsEmpty() || ApiKey.IsEmpty())
		{
			OnCompleteOnGameThread(false, TEXT("当前已切换到备用 REST 模式。请填写服务 URL、模型名，并设置 OPENAI_API_KEY；或移除 AUTO_UI_USE_REST 环境变量以恢复 Codex CLI 自动模式。"), TOptional<FAutoUILayoutSpec>());
			return;
		}

		if (PngBytes.Num() > MAX_int32)
		{
			OnCompleteOnGameThread(false, TEXT("纹理 PNG 体积过大，无法编码为 Base64。"), TOptional<FAutoUILayoutSpec>());
			return;
		}

		const FString Base64 = FBase64::Encode(PngBytes);
		const FString Body = AutoUIAiVision_Private::BuildRequestJson(Model, Base64, ImageWidth, ImageHeight);

		TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *ApiKey));
	Request->SetTimeout(180.f);
	Request->SetContentAsString(Body);

		Request->OnProcessRequestComplete().BindLambda(
		[OnCompleteOnGameThread, RequestUrl = FString(Url), ImageSourceLabel](
			FHttpRequestPtr Req,
			FHttpResponsePtr Resp,
			bool bProcessedSuccessfully) mutable
		{
			auto Finish = [OnCompleteOnGameThread](bool bOk, FString Msg, TOptional<FAutoUILayoutSpec> Spec = TOptional<FAutoUILayoutSpec>())
			{
				AsyncTask(ENamedThreads::GameThread, [OnCompleteOnGameThread, bOk, Msg = MoveTemp(Msg), Spec = MoveTemp(Spec)]() mutable
				{
					OnCompleteOnGameThread(bOk, Msg, Spec);
				});
			};

			// UE：bProcessedSuccessfully 表示 HTTP 层是否走完流程；失败时仍可能有 Resp，应读 FailureReason。
			if (!bProcessedSuccessfully)
			{
				FString Detail;
				if (Req.IsValid())
				{
					Detail += FString::Printf(
						TEXT("请求：状态=%s，原因=%s\n"),
						EHttpRequestStatus::ToString(Req->GetStatus()),
						LexToString(Req->GetFailureReason()));
				}
				if (Resp.IsValid())
				{
					Detail += FString::Printf(
						TEXT("响应：状态=%s，原因=%s，HTTP 码=%d\n"),
						EHttpRequestStatus::ToString(Resp->GetStatus()),
						LexToString(Resp->GetFailureReason()),
						Resp->GetResponseCode());
					const FString Snip = Resp->GetContentAsString().Left(800);
					if (!Snip.IsEmpty())
					{
						Detail += FString::Printf(TEXT("正文（截断）：\n%s\n"), *Snip);
					}
				}
				if (Detail.IsEmpty())
				{
					Detail = TEXT("（无更多诊断信息）\n");
				}
				Finish(false,
					FString::Printf(
						TEXT("HTTP 请求失败（未完成与服务器的往返）。\n%s\n请求 URL：%s\n")
						TEXT("说明：ConnectionError 多为网络/DNS/防火墙/证书；TimedOut 多为超时或上传体过大；Cancelled 为请求被取消。\n")
						TEXT("建议：在同一台电脑用 curl/PowerShell 对该 URL 发 POST 自检；或换较小分辨率纹理试跑。"),
						*Detail,
						*RequestUrl));
				return;
			}

			if (!Resp.IsValid())
			{
				Finish(false, FString::Printf(TEXT("HTTP 内部异常：已标记完成但响应为空。\n请求 URL：%s"), *RequestUrl));
				return;
			}

			const int32 Code = Resp->GetResponseCode();
			const FString ResponseStr = Resp->GetContentAsString();

			if (Code < 200 || Code >= 300)
			{
				Finish(false, FString::Printf(TEXT("HTTP %d\n%s"), Code, *ResponseStr.Left(4000)));
				return;
			}

			FString LayoutJson;
			FString ExtractErr;
			if (!AutoUIAiVision_Private::TryExtractLayoutJsonFromChatResponse(ResponseStr, LayoutJson, ExtractErr))
			{
				Finish(false, FString::Printf(TEXT("%s\n--- 原始响应（截断）---\n%s"), *ExtractErr, *ResponseStr.Left(4000)));
				return;
			}

			FString Message;
			TOptional<FAutoUILayoutSpec> Spec;
			const bool bOk = ParseAndValidateLayoutJson(LayoutJson, ImageSourceLabel + TEXT(" / REST"), Message, Spec);
			Finish(bOk, MoveTemp(Message), MoveTemp(Spec));
		});

		if (!Request->ProcessRequest())
		{
			OnCompleteOnGameThread(false, TEXT("无法发起 HTTP 请求（ProcessRequest 返回 false）。"), TOptional<FAutoUILayoutSpec>());
		}
	}
}

void AutoUIAiVision::RequestLayoutJsonFromPng(
	const TArray<uint8>& PngBytes,
	const int32 ImageWidth,
	const int32 ImageHeight,
	TFunction<void(bool bOk, FString Message, TOptional<FAutoUILayoutSpec> Spec)> OnCompleteOnGameThread)
{
	AutoUIAiVision_Private::RequestLayoutJsonFromPngInternal(
		PngBytes,
		ImageWidth,
		ImageHeight,
		TEXT("数学抠背景透明 PNG"),
		MoveTemp(OnCompleteOnGameThread));
}

void AutoUIAiVision::RequestLayoutJsonFromImage(
	UTexture2D* Texture,
	TFunction<void(bool bOk, FString Message, TOptional<FAutoUILayoutSpec> Spec)> OnCompleteOnGameThread)
{
	if (!OnCompleteOnGameThread)
	{
		return;
	}

	if (!Texture)
	{
		OnCompleteOnGameThread(false, TEXT("未选择纹理。"), TOptional<FAutoUILayoutSpec>());
		return;
	}

	FImage SourceImage;
	if (!FImageUtils::GetTexture2DSourceImage(Texture, SourceImage))
	{
		OnCompleteOnGameThread(false, TEXT("无法读取纹理源像素（可能无源数据或格式不支持）。请尝试使用带源数据的 Texture2D。"), TOptional<FAutoUILayoutSpec>());
		return;
	}

	TArray64<uint8> PngBytes64;
	if (!FImageUtils::CompressImage(PngBytes64, TEXT("png"), SourceImage) || PngBytes64.Num() == 0)
	{
		OnCompleteOnGameThread(false, TEXT("无法将当前纹理压缩为 PNG。请尝试使用普通 Texture2D 资源。"), TOptional<FAutoUILayoutSpec>());
		return;
	}

	TArray<uint8> PngBytes;
	PngBytes.Append(PngBytes64.GetData(), static_cast<int32>(PngBytes64.Num()));

	AutoUIAiVision_Private::RequestLayoutJsonFromPngInternal(
		PngBytes,
		Texture->GetSizeX(),
		Texture->GetSizeY(),
		TEXT("原始布局图"),
		MoveTemp(OnCompleteOnGameThread));
}
