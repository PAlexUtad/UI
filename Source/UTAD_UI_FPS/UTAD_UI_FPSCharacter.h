// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UTAD_UI_FPSCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class UTP_WeaponComponent;
struct FInputActionValue;

class UPlayerHUD;
class USkillTree;

DECLARE_DELEGATE_TwoParams(FOnPlayerHealthChanged, int /* NewHealth */, int /* MaxHealth */);
DECLARE_DELEGATE_OneParam(FOnTotalBulletsChanged, int /* TotalBullets */);

UCLASS(config=Game)
class AUTAD_UI_FPSCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Weapon component that is attached */
	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
	UTP_WeaponComponent* AttachedWeaponComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SkillAction;
public:
	AUTAD_UI_FPSCharacter();

protected:
	virtual void BeginPlay();

public:

	UPROPERTY()
	float PlayerMoney = 1000.0f;
	
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Current Health */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	int Health = 100;

	/** Max Health */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	int MaxHealth = 100;

	/** Counter for bullets in player (not in weapon) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	int TotalBullets = 100;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the int */
	UFUNCTION(BlueprintCallable, Category = Stats)
	void SetHealth(int NewHealth);

	/** Getter for the int */
	UFUNCTION(BlueprintCallable, Category = Stats)
	int GetHealth();

	/** Setter to set the int */
	UFUNCTION(BlueprintCallable, Category = Stats)
	void SetMaxHealth(int NewMaxHealth);

	/** Getter for the int */
	UFUNCTION(BlueprintCallable, Category = Stats)
	int GetMaxHealth();

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	/** Setter to set the int */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetTotalBullets(int NewTotalBullets);

	/** Getter for the int */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	int GetTotalBullets();

	/** Function to add an amount of bullets to TotalBullets */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void AddBullets(int Bullets);

	void SetAttachedWeaponComponent(UTP_WeaponComponent* WeaponComponent);

	// Delegates
	FOnPlayerHealthChanged OnPlayerHealthChanged;
	FOnTotalBulletsChanged OnTotalBulletsChanged;

	/****************************************************/
	/************************ UI ************************/
	/****************************************************/

	/** Widget Blueprints that will be used to create the instances */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<UPlayerHUD> PlayerHUDWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<UUserWidget> SkillTreeWidget;
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	void ToggleSkillTree(const FInputActionValue& Value);
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	/** Returns AttachedWeaponComponent subobject **/
	UTP_WeaponComponent* GetAttachedWeaponComponent() const { return AttachedWeaponComponent; }

private:

	/****************************************************/
	/************************ UI ************************/
	/****************************************************/

	/** Instances that will be created and shown on viewport */
	UPlayerHUD* PlayerHUDInstance;
	
	UUserWidget* SkillTreeInstance;
};

