// Fill out your copyright notice in the Description page of Project Settings.

#include "WallLamp.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "MainCharacter.h"

// Called when the object is activated
void AWallLamp::ActivateObject(AMainCharacter * character)
{
	if (Color == FLinearColor::Black)
		return;

	// UE_LOG(LogTemp, Warning, TEXT("Toggled lamp"));

	if (!IsOn())
		OnTurnOn();
	else
		OnTurnOff();

	Light->ToggleVisibility();
	UpdateMeshColor(IsOn() ? Color : FLinearColor::Black);
}

// TODO let some interface define it?
// Resets to initial state
void AWallLamp::Reset()
{
	Light->SetVisibility(false);
	UpdateMeshColor(FLinearColor::Black);
}

// Sets the color
void AWallLamp::SetColor(FLinearColor color)
{
	Color = color;
	Light->SetLightColor(color);
	if(Light->IsVisible())
		UpdateMeshColor(color);
}
// Returns the color
FLinearColor AWallLamp::GetColor()
{
	return Color;
}

// Returns true if lamp is on
bool AWallLamp::IsOn()
{
	return Light->IsVisible();
}

// Update's the color of the lamp mesh
void AWallLamp::UpdateMeshColor(FLinearColor color)
{
	Lamp->SetVectorParameterValueOnMaterials("Color", FVector(color.R, color.G, color.B));
}

// Sets default values
AWallLamp::AWallLamp()
{
	// Create root component
	Direction = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	SetRootComponent(Direction);

	// Create the lamp itself
	Lamp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lamp"));
	Lamp->SetupAttachment(RootComponent);

	// Create the light
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(RootComponent);

	// Fill information
	Name = NSLOCTEXT("LocalNS", "Wall lamp name", "Wall lamp");
	BasicInfo = NSLOCTEXT("LocalNS", "Wall lamp information", "Provides light in the lab");

	// Set activatable parameters
	bActivatableDirectly = false;
	bActivatableIndirectly = true;
}

// Called when the game starts or when spawned
void AWallLamp::BeginPlay()
{
	Super::BeginPlay();

	// Lamp is disabled
	Reset();
}