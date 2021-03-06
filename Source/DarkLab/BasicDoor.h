// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicActivatableObject.h"
#include "BasicDoor.generated.h"

// A openable simple door
UCLASS()
class DARKLAB_API ABasicDoor : public ABasicActivatableObject
{
	GENERATED_BODY()

public:
	// Called when the object is activated
	UFUNCTION(BlueprintCallable, Category = "Activatable")
	virtual void ActivateObject(AMainCharacter* character) override;

	// TODO let some interface define it?
	// Resets to initial state
	UFUNCTION(BlueprintCallable, Category = "Door")
	void ResetDoor(bool isExit);

	// Called when opening
	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void OnOpen();
	// Called when closing
	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void OnClose();
	// Called when opening failed
	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void OnOpenFailed();
	// Called when opening exit
	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void OnOpenExit();
	
protected:
	// Door's direction and root object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door: Components")
	class UArrowComponent* Direction;

	// Door's frame
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door: Components")
	class UStaticMeshComponent* DoorFrame;

	// Timeline, driving the door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door: Components")
	class UTimelineComponent* DoorDriver;

	// If true, this is an exit door
	bool bIsExit = false;

public:
	// The color of panels on the door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	FLinearColor DoorColor = FLinearColor::White;
	
public:
	// Sets default values
	ABasicDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};