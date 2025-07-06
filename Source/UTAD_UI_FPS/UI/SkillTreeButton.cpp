
/**
 *	USkillTreeButton
 *	Implementation of the button unlocking abilities
 */
 
#include "SkillTreeButton.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void USkillTreeButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (SkillButton)
	{
		DefaultButtonStyle = SkillButton->WidgetStyle;
		SkillButton->OnPressed.AddDynamic(this, &USkillTreeButton::OnPressed);
		SkillButton->OnReleased.AddDynamic(this, &USkillTreeButton::OnReleased);
	}
}

void USkillTreeButton::Init(int32 Index, float Cost, const FString& Label)
{
	ButtonIndex = Index;
	SkillCost = Cost;
	if (ButtonLabel)
	{
		ButtonLabel->SetText(FText::FromString(Label));
	}
	if (CostText)
	{
		FString CostString = FString::Printf(TEXT("%.0f"), Cost);
		CostText->SetText(FText::FromString(CostString));
	}
}

void USkillTreeButton::OnPressed()
{
	bIsHolding = true;
	HoldTime = 0.0f;
}

void USkillTreeButton::OnReleased()
{
	bIsHolding = false;
	HoldTime = 0.0f;
	UpdateProgress(0.0f);
}

void USkillTreeButton::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	

	if (bIsHolding)
	{
		HoldTime += InDeltaTime;
		const float Progress = FMath::Clamp(HoldTime / MaxHoldTime, 0.0f, 1.0f);
		UpdateProgress(Progress);
		if (Progress >= 1.0f)
		{
			bIsHolding = false;
			HoldTime = 0.0f;
			UpdateProgress(1.0f);
			// Notify parent widget (SkillTree)
			OnSkillUnlocked.Broadcast(ButtonIndex);
		}
	}
}

void USkillTreeButton::SetButtonGreen() const
{
	if (SkillButton)
	{
		FButtonStyle ButtonStyle = SkillButton->WidgetStyle;

		FSlateBrush NormalBrush = ButtonStyle.Normal;
		NormalBrush.TintColor = FLinearColor::Green;
		ButtonStyle.SetNormal(NormalBrush);

		FSlateBrush HoveredBrush = ButtonStyle.Hovered;
		HoveredBrush.TintColor = FLinearColor(0.0f, 0.5f, 0.0f, 1.0f);
		ButtonStyle.SetHovered(HoveredBrush);

		FSlateBrush PressedBrush = ButtonStyle.Pressed;
		PressedBrush.TintColor = FLinearColor(0.0f, 0.8f, 0.0f, 1.0f);
		ButtonStyle.SetPressed(PressedBrush);

		SkillButton->SetStyle(ButtonStyle);
	}
}


void USkillTreeButton::UpdateProgress(float Value) const
{
	if (ProgressBar)
	{
		ProgressBar->SetPercent(Value);
	}
}

void USkillTreeButton::FlashRed()
{
	if (!SkillButton) return;

	FButtonStyle ButtonStyle = SkillButton->WidgetStyle;

	FSlateBrush NormalBrush = ButtonStyle.Normal;
	NormalBrush.TintColor = FLinearColor::Red;
	ButtonStyle.SetNormal(NormalBrush);

	FSlateBrush HoveredBrush = ButtonStyle.Hovered;
	HoveredBrush.TintColor = FLinearColor(0.6f, 0.0f, 0.0f, 1.0f);
	ButtonStyle.SetHovered(HoveredBrush);

	FSlateBrush PressedBrush = ButtonStyle.Pressed;
	PressedBrush.TintColor = FLinearColor(0.8f, 0.0f, 0.0f, 1.0f);
	ButtonStyle.SetPressed(PressedBrush);

	SkillButton->SetStyle(ButtonStyle);

	// Reset color back to default after a short delay
	GetWorld()->GetTimerManager().SetTimer(RedFlashTimerHandle, this, &USkillTreeButton::ResetButtonStyle, 0.5f, false);
}

void USkillTreeButton::ResetButtonStyle() const
{
	if (bIsUnlocked)
	{
		SetButtonGreen();
	}
	else
	{
		SkillButton->SetStyle(DefaultButtonStyle);
	}
}
