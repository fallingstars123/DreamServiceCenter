#include "LetterDescriptionWidget.h"

#include "Components/TextBlock.h"


void ULetterDescriptionWidget::ApplyLetterContent(
    const FText& Title,
    const FText& Description
)
{
    if (IsValid(LetterTitleTextBlock))
    {
        LetterTitleTextBlock->SetText(Title);
    }


    if (IsValid(LetterBodyTextBlock))
    {
        LetterBodyTextBlock->SetText(Description);
        LetterBodyTextBlock->SetAutoWrapText(true);
    }


    // Preserve the existing Blueprint event so older widget Blueprints keep
    // working while the optional native bindings are introduced.
    SetupLetterContent(
        Title,
        Description
    );
}
