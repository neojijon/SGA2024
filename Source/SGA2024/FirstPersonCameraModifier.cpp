// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonCameraModifier.h"


void UFirstPersonCameraModifier::ModifyCamera(float DeltaTime, FVector ViewLocation, FRotator ViewRotation, float FOV,
	FVector& NewViewLocation, FRotator& NewViewRotation, float& NewFOV)
{
	Super::ModifyCamera(DeltaTime, ViewLocation, ViewRotation, FOV, NewViewLocation, NewViewRotation, NewFOV);

	const FTransform viewTransform(ViewRotation, ViewLocation, FVector(1.0f, 1.0f, 1.0f));

	NewViewLocation = viewTransform.TransformPosition(FVector(-CameraParams.HorizontalOffset, 0.0f, CameraParams.VerticalOffset));
}

void UFirstPersonCameraModifier::ModifyPostProcess(float deltaTime, float& postProcessBlendWeight,
	FPostProcessSettings& postProcessSettings)
{
	Super::ModifyPostProcess(deltaTime, postProcessBlendWeight, postProcessSettings);

	postProcessSettings = PostProcessSettings;
	postProcessBlendWeight = 1.0f;
}