// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "FirstPersonCameraModifier.generated.h"

USTRUCT(BlueprintType)
struct FFirstPersonModifierParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float VerticalOffset = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HorizontalOffset = 200.0f;
};


UCLASS()
class SGA2024_API UFirstPersonCameraModifier : public UCameraModifier
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FFirstPersonModifierParams CameraParams;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPostProcessSettings PostProcessSettings;

protected:
	virtual void ModifyCamera(float DeltaTime, FVector ViewLocation, FRotator ViewRotation, float FOV, FVector& NewViewLocation, FRotator& NewViewRotation, float& NewFOV) override;

	virtual void ModifyPostProcess(float deltaTime, float& postProcessBlendWeight, FPostProcessSettings& postProcessSettings) override;
	
};
