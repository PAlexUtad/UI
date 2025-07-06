/**
 *	USkillTree
 *	Definition of the branch with X buttons
 */
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTree.generated.h"

class USkillTreeMenu;
class UVerticalBox;
class AUTAD_UI_FPSCharacter;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API USkillTree : public UUserWidget
{
	GENERATED_BODY()

	bool bIsHolding = false;
	float HoldTime = 0.0f;
	float MaxHoldTime = 0.5f;
	int focusBtn = 0;
public:
	// Constructor
	USkillTree(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ButtonContainer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill Tree")
	TSubclassOf<class USkillTreeButton> SkillTreeButtonClass;

	TArray<USkillTreeButton*> CreatedButtons;
protected:

	// Called when the game starts or when spawned

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnSkillButtonUnlocked(int32 ButtonIndex);
	
	// List of skill costs
	UPROPERTY()
	TArray<float> SkillCost;

	UPROPERTY()
	AUTAD_UI_FPSCharacter* PlayerChar;

	UPROPERTY()
	float DefaultCostVal;

public:
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Show();

	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Hide();

	bool CanUnlockButton(int32 ButtonIndex);
	void AddMoney(float Amount) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Tree")
	TArray<FString> NodeLabels = { "Unlock Button 1", "Unlock Button 2", "Final Ability" };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Tree")
	TArray<float> NodeCosts = { 100.0f, 200.0f, 300.0f };

	UPROPERTY()
	USkillTreeMenu* OwningMenu;

};


