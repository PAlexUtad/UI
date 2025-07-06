/**
 *	USkillTreeButton
 *	Definition of the button unlocking abilities
 */
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTreeButton.generated.h"

class UProgressBar;
class UButton;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillButtonComplete, int32, ButtonIndex);

UCLASS()
class UTAD_UI_FPS_API USkillTreeButton : public UUserWidget
{
	GENERATED_BODY()

public:

	bool bIsUnlocked = false;
	
	UPROPERTY(meta = (BindWidget))
	UButton* SkillButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonLabel;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CostText;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	int32 ButtonIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	float SkillCost;

	UPROPERTY(BlueprintAssignable)
	FOnSkillButtonComplete OnSkillUnlocked;

	void Init(int32 Index, float Cost, const FString& Label);
	void SetButtonGreen() const;
	void UpdateProgress(float Value) const;
	void FlashRed();
	void ResetButtonStyle() const;

protected:
	virtual void NativeConstruct() override;

private:
	FButtonStyle DefaultButtonStyle;
	FTimerHandle RedFlashTimerHandle;

	bool bIsHolding = false;
	float HoldTime = 0.0f;
	const float MaxHoldTime = 0.5f;

	UFUNCTION()
	void OnPressed();

	UFUNCTION()
	void OnReleased();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};