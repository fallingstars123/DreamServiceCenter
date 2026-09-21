#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LetterDescriptionWidget.generated.h"

class UTextBlock;


UCLASS()
class LETTERINSPECTION_API ULetterDescriptionWidget : public UUserWidget
{
    GENERATED_BODY()


public:

    /**
     * Applies the letter data to the optional native text bindings, then
     * forwards the same values to SetupLetterContent for backwards-compatible
     * Blueprint customization.
     *
     * In the Widget Blueprint, create variable Text Blocks named:
     * - LetterTitleTextBlock
     * - LetterBodyTextBlock
     */
    UFUNCTION(
        BlueprintCallable,
        Category = "Letter"
    )
    void ApplyLetterContent(
        const FText& Title,
        const FText& Description
    );


    /**
     * Optional title binding in the derived Widget Blueprint.
     */
    UPROPERTY(
        BlueprintReadOnly,
        meta = (BindWidgetOptional),
        Category = "Letter"
    )
    TObjectPtr<UTextBlock> LetterTitleTextBlock;


    /**
     * Optional display-only paragraph binding. The native implementation
     * enables automatic wrapping so long descriptions behave like body copy
     * instead of a second heading.
     */
    UPROPERTY(
        BlueprintReadOnly,
        meta = (BindWidgetOptional),
        Category = "Letter"
    )
    TObjectPtr<UTextBlock> LetterBodyTextBlock;


    UFUNCTION(
        BlueprintImplementableEvent,
        Category = "Letter"
    )
    void SetupLetterContent(
        const FText& Title,
        const FText& Description
    );
};
