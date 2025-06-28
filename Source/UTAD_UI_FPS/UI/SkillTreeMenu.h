#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTreeMenu.generated.h"

class UTextBlock;
class AUTAD_UI_FPSCharacter;

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API USkillTreeMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	AUTAD_UI_FPSCharacter* PlayerChar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerMoneyText;

public:
	void UpdatePlayerMoneyDisplay() const;
};
