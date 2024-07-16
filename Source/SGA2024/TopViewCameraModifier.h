// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "TopViewCameraModifier.generated.h"

USTRUCT(BlueprintType)
struct FTopViewModifierParams
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector LocationOffset = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FRotator RotationOverride = FRotator::ZeroRotator;
};


UCLASS()
class SGA2024_API UTopViewCameraModifier : public UCameraModifier
{
	GENERATED_BODY()


public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FTopViewModifierParams LocationParams;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPostProcessSettings PostProcessSettings;

	// Sets default values for this actor's properties
	UTopViewCameraModifier(const FObjectInitializer& ObjectInitializer);


protected:
	virtual void ModifyCamera(float deltaTime, FVector viewLocation, FRotator viewRotation, float fov, FVector& newViewLocation, FRotator& newViewRotation, float& newFOV) override;

	virtual void ModifyPostProcess(float deltaTime, float& postProcessBlendWeight, FPostProcessSettings& postProcessSettings) override;


};
