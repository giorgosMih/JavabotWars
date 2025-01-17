// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Components/RichTextBlockDecorator.h"
#include "Components/Widget.h"
#include "RichTextBox.generated.h"


UCLASS() 
class UETUTORIAL_API URichTextBox : public UWidget
{
	GENERATED_BODY()
	
	
public:
	URichTextBox(const FObjectInitializer& ObjectInitializer);

	// UWidget interface
	virtual void SynchronizeProperties() override;
	// End of UWidget interface

	// UVisual interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	// End of UVisual interface

	// Sets the text of this Rich Text
	UFUNCTION(BlueprintCallable, Category = "Rich Text")
		void SetText(FText InText);

	UFUNCTION(BlueprintPure, Category = "Rich Text")
		FText GetText();

#if WITH_EDITOR
	// UWidget interface
	//virtual const FSlateBrush* GetEditorIcon() override;
	virtual const FText GetPaletteCategory() override;
	// End UWidget interface
#endif

protected:
	/** The text to display */
	UPROPERTY(EditAnywhere, Category = Content, meta = (MultiLine = "true"))
		FText Text;

	/** A bindable delegate to allow logic to drive the text of the widget */
	UPROPERTY()
		FGetText TextDelegate;

	/** The default color for the text. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		FLinearColor ColorAndOpacity;

	/** The default font for the text. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		FSlateFontInfo Font;

	/** The direction the shadow is cast */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		FVector2D ShadowOffset;

	/** The color of the shadow */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, meta = (DisplayName = "Shadow Color"))
		FLinearColor ShadowColorAndOpacity;


	/** How the text should be aligned with the margin. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		TEnumAsByte<ETextJustify::Type> Justification;

	/** True if we're wrapping text automatically based on the computed horizontal space for this widget */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		bool AutoWrapText;

	/** Whether text wraps onto a new line when it's length exceeds this width; if this value is zero or negative, no wrapping occurs. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, AdvancedDisplay)
		float WrapTextAt;

	/** The amount of blank space left around the edges of text area. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, AdvancedDisplay)
		FMargin Margin;

	/** The amount to scale each lines height by. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, AdvancedDisplay)
		float LineHeightPercentage;

	UPROPERTY(EditAnywhere, Instanced, Category = Decorators)
		TArray<class URichTextBlockDecorator*> Decorators;

protected:
	FTextBlockStyle DefaultStyle;

	/** Native Slate Widget */
	TSharedPtr<SRichTextBlock> MyRichTextBlock;

	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface
	
};
