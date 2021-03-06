// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicActivatableObject.h"
#include "WallLamp.generated.h"

// A lamp in the wall
UCLASS()
class DARKLAB_API AWallLamp : public ABasicActivatableObject
{
	GENERATED_BODY()
	
public:
	// Called when the object is activated
	UFUNCTION(BlueprintCallable, Category = "Activatable")
	virtual void ActivateObject(AMainCharacter* character) override;

	// TODO let some interface define it?
	// Resets to initial state
	UFUNCTION(BlueprintCallable, Category = "Lamp")
	void Reset();

	// Sets the color
	UFUNCTION(BlueprintCallable, Category = "Lamp")
	void SetColor(FLinearColor color);
	// Returns the color
	UFUNCTION(BlueprintCallable, Category = "Lamp")
	FLinearColor GetColor();

	// Returns true if lamp is on
	UFUNCTION(BlueprintCallable, Category = "Lamp")
	bool IsOn();

	// Called when turned on
	UFUNCTION(BlueprintImplementableEvent, Category = "Lamp")
	void OnTurnOn();
	// Called when turned off
	UFUNCTION(BlueprintImplementableEvent, Category = "Lamp")
	void OnTurnOff();

private:
	// Update's the color of the lamp mesh
	UFUNCTION()
	void UpdateMeshColor(FLinearColor color);

protected:
	// Lamp's direction and root object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lamp: Components")
	class UArrowComponent* Direction;

	// The lamp itself
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lamp: Components")
	class UStaticMeshComponent* Lamp;

	// The lamp's light
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lamp: Components")
	class UPointLightComponent* Light;

protected:
	// The color of light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lamp")
	FLinearColor Color = FLinearColor::White;
	
public:
	// Sets default values
	AWallLamp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};