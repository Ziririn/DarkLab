// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

// The main character of the game
UCLASS(Blueprintable)
class DARKLAB_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Movement 
	void MoveUp(const float value);
	void MoveRight(const float value);
	void Look(const FVector direction);

	// Other controls
	void UseEquiped();
	void Activate();

	// Takes one 'life' and calls CalculateLoss
	UFUNCTION(BlueprintCallable, Category = "Main Character")
	void TakeLife();

private:
	// Checks for the loss
	void CalculateLoss();
	// Called on loss
	void OnLoss();

	// The coefficient for the movement backwards
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main Character", meta = (AllowPrivateAccess = "true"))
	float BackMoveCoeff = 0.6f;

	// The number of character's 'lives'
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main Character", meta = (AllowPrivateAccess = "true"))
	int Lives = 1;

	// Camera boom positioning the camera above the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main Character", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// Top down camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main Character", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCamera;

	// A reference to the game mode
	class AMainGameMode* GameMode;

	// TODO delete later
	TSubclassOf<class AFlashlight> MyFlashlightBP;

public:
	// Some equiped object
	class IEquipable* EquipedObject;

	// Is true when a character loses a life. Used for "death" animation
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main Character")
	bool bIsDisabled = false;

public:
	// Sets default values
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(const float deltaTime) override;
};