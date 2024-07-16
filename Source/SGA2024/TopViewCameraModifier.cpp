// Fill out your copyright notice in the Description page of Project Settings.


#include "TopViewCameraModifier.h"

#include "SGA2024/MyPlayerController.h"

UTopViewCameraModifier::UTopViewCameraModifier(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void UTopViewCameraModifier::ModifyCamera(float deltaTime, FVector viewLocation, FRotator viewRotation, float fov,
	FVector& newViewLocation, FRotator& newViewRotation, float& newFOV)
{
	Super::ModifyCamera(deltaTime, viewLocation, viewRotation, fov, newViewLocation, newViewRotation, newFOV);

	newViewLocation = viewLocation + LocationParams.LocationOffset;
	newViewRotation = LocationParams.RotationOverride;

}

void UTopViewCameraModifier::ModifyPostProcess(float deltaTime, float& postProcessBlendWeight,
	FPostProcessSettings& postProcessSettings)
{
	Super::ModifyPostProcess(deltaTime, postProcessBlendWeight, postProcessSettings);

	postProcessSettings = PostProcessSettings;
	postProcessBlendWeight = 1.0f;
}