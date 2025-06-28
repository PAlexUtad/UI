#include "SkillTreeMenu.h"
#include "Components/TextBlock.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"
#include "GameFramework/PlayerController.h"


void USkillTreeMenu::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PC = GetOwningPlayer();
	if (IsValid(PC))
	{
		if (APawn* Pawn = PC->GetPawn())
		{
			PlayerChar = Cast<AUTAD_UI_FPSCharacter>(Pawn);
		}
	}

	UpdatePlayerMoneyDisplay();
}

void USkillTreeMenu::UpdatePlayerMoneyDisplay() const
{
	if (PlayerMoneyText && PlayerChar)
	{
		const FString MoneyString = FString::Printf(TEXT("Available Funds: %f"), PlayerChar->PlayerMoney);
		PlayerMoneyText->SetText(FText::FromString(MoneyString));
	}
}
