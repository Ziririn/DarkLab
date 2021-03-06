// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicPickupableObject.h"
#include "Equipable.h"
#include "BasicEquipableObject.generated.h"

// Represents objects with physical representation that can be equiped by the main character
UCLASS()
class DARKLAB_API ABasicEquipableObject : public ABasicPickupableObject, public IEquipable
{
	GENERATED_BODY()

public:
	// Called when the object is to be equiped
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Equipable")
	void Equip(AMainCharacter* character, const FName location);
	virtual void Equip_Implementation(AMainCharacter* character, const FName location) override;
	
	// Called when the object is to be unequiped
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Equipable")
	void Unequip(AMainCharacter* character);
	virtual void Unequip_Implementation(AMainCharacter* character) override;

	// Called when the object is activated (picked up in the laboratory)
	UFUNCTION(BlueprintCallable, Category = "Activatable")
	virtual void ActivateObject(AMainCharacter* character) override;

	// Called when equiped
	UFUNCTION(BlueprintImplementableEvent, Category = "Equipable")
	void OnEquip();
	// Called when unequiped
	UFUNCTION(BlueprintImplementableEvent, Category = "Equipable")
	void OnUnequip();

// public:
	// Sets default values
	// ABasicEquipableObject();
};