
/**
 *	USkillTree
 *	Implementation of the branch with X buttons
 */
 
#include "SkillTree.h"

#include "SkillTreeButton.h"
#include "SkillTreeMenu.h"
#include "Components/VerticalBox.h"
#include "Styling/SlateBrush.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"


USkillTree::USkillTree(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultCostVal = 100.0f;
}

void USkillTree::NativeConstruct()
{
	Super::NativeConstruct();

	if (APlayerController* PC = GetOwningPlayer())
	{
		if (APawn* Pawn = PC->GetPawn())
		{
			PlayerChar = Cast<AUTAD_UI_FPSCharacter>(Pawn);
		}
	}

	if (NodeLabels.Num() > NodeCosts.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Skill Cost item missing! Adding default costs..."));
		for (int32 i = NodeCosts.Num(); i < NodeLabels.Num(); ++i)
		{
			NodeCosts.Add(DefaultCostVal);
		}
	}

	if (SkillTreeButtonClass && ButtonContainer)
	{
		for (int32 i = 0; i < NodeLabels.Num(); ++i)
		{
			USkillTreeButton* NewButton = CreateWidget<USkillTreeButton>(this, SkillTreeButtonClass);
			if (NewButton)
			{
				NewButton->Init(i, NodeCosts[i], NodeLabels[i]);
				NewButton->OnSkillUnlocked.AddDynamic(this, &USkillTree::OnSkillButtonUnlocked);
				ButtonContainer->AddChild(NewButton);
				CreatedButtons.Add(NewButton);
				NewButton->SetIsEnabled(i == 0); // Only first enabled
			}
		}
	}

	OwningMenu = GetTypedOuter<USkillTreeMenu>();
}

void USkillTree::OnSkillButtonUnlocked(int32 ButtonIndex)
{
	if (!PlayerChar || !CreatedButtons.IsValidIndex(ButtonIndex))
		return;

	USkillTreeButton* Btn = CreatedButtons[ButtonIndex];
	if (PlayerChar->PlayerMoney >= Btn->SkillCost)
	{
		PlayerChar->PlayerMoney -= Btn->SkillCost;
		Btn->SetIsEnabled(false);
		Btn->SetButtonGreen(); 
		Btn->bIsUnlocked = true;

		if (CreatedButtons.IsValidIndex(ButtonIndex + 1))
		{
			CreatedButtons[ButtonIndex + 1]->SetIsEnabled(true);
		}
		if (OwningMenu)
		{
			OwningMenu->UpdatePlayerMoneyDisplay();
		}
	}
	else
	{
		Btn->FlashRed();
		UE_LOG(LogTemp, Warning, TEXT("Not enough money to unlock skill %d"), ButtonIndex);
	}
}


bool USkillTree::CanUnlockButton(int32 ButtonIndex)
{
	if (SkillCost.IsValidIndex(ButtonIndex - 1) && PlayerChar && PlayerChar->PlayerMoney >= SkillCost[ButtonIndex - 1])
	{
		return true;
	}
	return false;
}

void USkillTree::AddMoney(float Amount) const
{
	if (PlayerChar)
	{
		PlayerChar->PlayerMoney += Amount;
	}
}

void USkillTree::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void USkillTree::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}