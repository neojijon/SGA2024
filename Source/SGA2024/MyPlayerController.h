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
	void SwitchCameraMode(); //Tab키

	void SetCameraFirstMode();// 숫자 1키
	void SetCameraThirdMode();// 숫자 2키
	void SetCameraTopViewMode();// 숫자 3키

	UCameraComponent* GetFollowCamera();

	ECameraMode CameraMode = ECameraMode::ThirdMode;
	ECameraMode PrevCameraMode = ECameraMode::TopView;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_CameraChangeMode; //tab키
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_FirstMode;  //1	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ThirdMode; //2

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_TopView; // 3

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* IMC_Camera;

};
