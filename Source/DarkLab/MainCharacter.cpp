// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Equipable.h"
#include "Usable.h"
#include "Activatable.h"
#include "MainPlayerController.h"
#include "MainGameMode.h"
// For on screen debug
#include "EngineGlobals.h"
#include "Engine/Engine.h"
// TODO delete later?
/*
#include "Flashlight.h"
#include "UObject/ConstructorHelpers.h"
*/
#include "Components/CapsuleComponent.h"

// Movement functions
void AMainCharacter::MoveUp(const float value)
{
	FRotator rotation = GetActorRotation();
	FVector direction = rotation.Vector();
	FVector v2 = FVector(1.0f, 0.0f, 0.0f) * value;
	// Angle between applied movement and view direction
	float angle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(direction, v2)));

	// Movement is slower when looking in the opposite direction of movement
	AddMovementInput(FVector(1.0f - (1.0f - BackMoveCoeff) * angle / 180.0f, 0.0f, 0.0f), value);
}
void AMainCharacter::MoveRight(const float value)
{
	FRotator rotation = GetActorRotation();
	FVector direction = rotation.Vector();
	FVector v2 = FVector(0.0f, 1.0f, 0.0f) * value;
	// Angle between applied movement and view direction
	float angle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(direction, v2)));

	// Movement is slower when looking in the opposite direction of movement
	AddMovementInput(FVector(0.0f, 1.0f - (1.0f - BackMoveCoeff) * angle / 180.0f, 0.0f), value);
}
void AMainCharacter::Look(const FVector direction)
{
	SetActorRotation(direction.Rotation());
}

// Uses equiped object if it is IUsable
void AMainCharacter::UseEquiped()
{
	if (!EquipedObject)
		return;

	IUsable* toUse = Cast<IUsable>(EquipedObject->_getUObject());
	if (toUse)
		toUse->Execute_Use(EquipedObject->_getUObject());
}

// Activates nearby object on scene
void AMainCharacter::Activate()
{
	if (ActivatableObjects.Num() == 0)
		return;

	UE_LOG(LogTemp, Warning, TEXT("Activated"));

	// TODO should take the closet one in front, not the first one
	TScriptInterface<IActivatable> toActivate = ActivatableObjects[0];
	toActivate->Execute_Activate(toActivate->_getUObject(), this);
}

// Happens when something 'damages' the character
void AMainCharacter::Disable()
{
	UE_LOG(LogTemp, Warning, TEXT("Got disabled"));

	bIsDisabled = true;

	// TODO destroy instead?
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	PrimaryActorTick.SetTickFunctionEnable(false);

	// Tell the controller that we got disabled
	AMainPlayerController* controller = Cast<AMainPlayerController>(GetController());
	if (controller)
		controller->OnDisabled();

	// TODO Destroy?
}

// Used for the activator's collision overlaps
void AMainCharacter::OnActivatorBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// We don't count our currently equiped object
	UObject* otherObject = Cast<UObject>(OtherActor);
	if (EquipedObject && otherObject == EquipedObject->_getUObject())
		return;

	UE_LOG(LogTemp, Warning, TEXT("Found activatable"));

	ActivatableObjects.AddUnique(OtherActor);
}
void AMainCharacter::OnActivatorEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	// We don't count our currently equiped object
	UObject* otherObject = Cast<UObject>(OtherActor);
	if (EquipedObject && otherObject == EquipedObject->_getUObject())
		return;

	UE_LOG(LogTemp, Warning, TEXT("Lost activatable"));

	ActivatableObjects.Remove(OtherActor);
}

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Create a camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	// Create a camera
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Create an activator
	Activator = CreateDefaultSubobject<UBoxComponent>(TEXT("Activator"));
	Activator->SetupAttachment(RootComponent);
	Activator->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnActivatorBeginOverlap);
	Activator->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::OnActivatorEndOverlap);

	// TODO delete later
	// this can be used somewhere
	// we shouldn't find blueprints from character
	/*
	static ConstructorHelpers::FObjectFinder<UClass> flashlightBP(TEXT("Class'/Game/Blueprints/FlashlightBP.FlashlightBP_C'"));
	if (flashlightBP.Object)
		MyFlashlightBP = flashlightBP.Object;
	*/

 	// Set this character to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	
	// TODO delete later
	// this can be used somewhere
	// we shouldn't spawn objects from character
	// nor should we equip like this
	/*
	AFlashlight* flashlight = GetWorld()->SpawnActor<AFlashlight>(MyFlashlightBP, GetActorLocation(), GetActorRotation());
	if (flashlight)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawned a flashlight"));
		IEquipable* toEquip = Cast<IEquipable>(flashlight);
		if (toEquip)
			toEquip->Execute_Equip(flashlight, this, FName("LeftHand"));
	}
	*/
}

// Called every frame
void AMainCharacter::Tick(const float deltaTime)
{
	Super::Tick(deltaTime);

	// TODO delete
	// We check the light level
	// GameMode->GetLightingAmount(this, true);

	// TODO delete later: used for debug
	if (GEngine)
	{
		// TODO show the name of activatable
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("Activatable: %s"), ActivatableObjects.Num() > 0 ? TEXT("Flashlight") : TEXT("None")), true);

		// TODO show the name of equiped
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("Equiped: %s"), EquipedObject ? TEXT("Flashlight") : TEXT("None")), true);

		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, TEXT(""), true);
	}
}