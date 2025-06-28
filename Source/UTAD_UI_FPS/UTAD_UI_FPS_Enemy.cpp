// Fill out your copyright notice in the Description page of Project Settings.


#include "UTAD_UI_FPS_Enemy.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/EnemyHealthBar.h"
#include "Components/WidgetComponent.h"

void AUTAD_UI_FPS_Enemy::BeginPlay()
{
	PrimaryActorTick.bCanEverTick = true;

	Super::BeginPlay();
}

void AUTAD_UI_FPS_Enemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AUTAD_UI_FPS_Enemy::SetHealth(int NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0, MaxHealth);
	if (Health == 0)
	{
		Destroy();
	}
}

int AUTAD_UI_FPS_Enemy::GetHealth()
{
	return Health;
}

void AUTAD_UI_FPS_Enemy::SetMaxHealth(int NewMaxHealth)
{
	MaxHealth = FMath::Max(0, NewMaxHealth);
}

int AUTAD_UI_FPS_Enemy::GetMaxHealth()
{
	return MaxHealth;
}