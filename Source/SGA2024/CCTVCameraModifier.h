// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "CCTVCameraModifier.generated.h"

/**
 * 
 */
UCLASS()
class SGA2024_API UCCTVCameraModifier : public UCameraModifier
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPostProcessSettings PostProcessSettings;

	virtual void ModifyCamera(float deltaTime, FVector viewLocation, FRotator viewRotation, float fov, FVector& newViewLocation, FRotator& newViewRotation, float& newFOV) override;

	virtual void ModifyPostProcess(float deltaTime, float& postProcessBlendWeight, FPostProcessSettings& postProcessSettings) override;

};
