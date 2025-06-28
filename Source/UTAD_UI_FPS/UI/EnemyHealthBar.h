// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UEnemyHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Update the player health bar with the given value */
	UFUNCTION(BlueprintCallable)
	void UpdateEnemyHealthBarValue(int Value, int MaxValue);
};
