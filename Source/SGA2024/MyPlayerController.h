// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;


UENUM(BlueprintType)
enum ECameraMode
{
	FirstMode,
	ThirdMode,
	TopView,		
	Default
};


/**
 * 
 */
UCLASS()
class SGA2024_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()


public:	
	AMyPlayerController(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	void SwitchCameraMode(); //TabŰ

	void SetCameraFirstMode();// ���� 1Ű
	void SetCameraThirdMode();// ���� 2Ű
	void SetCameraTopViewMode();// ���� 3Ű

	UCameraComponent* GetFollowCamera();

	ECameraMode CameraMode = ECameraMode::ThirdMode;
	ECameraMode PrevCameraMode = ECameraMode::TopView;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_CameraChangeMode; //tabŰ
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_FirstMode;  //1	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ThirdMode; //2

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_TopView; // 3

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* IMC_Camera;

};
