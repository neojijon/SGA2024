// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "MyPlayerCameraManager.generated.h"

class UCameraModifier;
class UCCTVCameraModifier;
class UFirstPersonCameraModifier;
class UThirdPersonCameraModifier;
class UTopViewCameraModifier;



UENUM(BlueprintType)
enum ECameraMode
{
	FirstPersonMode,
	ThirdPersonMode,
	TopViewMode,
	CCTVMode,
	Default
};



UCLASS()
class SGA2024_API AMyPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraModifier> TopViewCameraModifier;// = UTopViewCameraModifier::StaticClass();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraModifier> ThirdPersonCameraModifier;// = UThirdPersonCameraModifier::StaticClass();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraModifier> FirstPersonCameraModifier;// = UFirstPersonCameraModifier::StaticClass();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraModifier> CCTVCameraModifier;// = UCCTVCameraModifier::StaticClass();

protected:
	ECameraMode CameraMode = ECameraMode::TopViewMode;

	ECameraMode PreviousCameraMode = ECameraMode::ThirdPersonMode;


public:
	ECameraMode GetPreviousCameraMode() const { return PreviousCameraMode; }

	ECameraMode GetCameraMode() const { return CameraMode; }

	void SetCameraMode(ECameraMode newCameraMode);
	
};
