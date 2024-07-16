// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerCameraManager.h"
#include "MyPlayerController.generated.h"


struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;

class UCameraModifier;
//class AMyPlayerCameraManager;

//
//UENUM(BlueprintType)
//enum ECameraMode
//{
//	FirstPersonMode,
//	ThirdPersonMode,
//	TopView,
//	CCTVMode,
//	Default
//};

//델리게이트 선언 ECameraMode 타입의 newCameraMode와 oldCameraMode라는 두 개의 파라미터를 받습니다.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCameraModeChangedSignature, ECameraMode, newCameraMode, ECameraMode, oldCameraMode);

UCLASS()
class SGA2024_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()


public:	
	AMyPlayerController(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


	//플레이어 카메라 메니저 초기화해주는 역할
	virtual void SpawnPlayerCameraManager() override;

	//Pawn 
	virtual void OnPossess(APawn* InPawn) override;

	// 델리게이트 인스턴스
	UPROPERTY(BlueprintAssignable, Category = PlayerController)
	FOnCameraModeChangedSignature OnCameraModeChangedDelegate;


protected:
	TWeakObjectPtr<AMyPlayerCameraManager> _MyPlayerCameraManager;


public:

	void SwapCameraMode();
	void SwitchCameraMode(); //Tab키

	ECameraMode GetCameraMode();

	void SetCameraFirstMode();// 숫자 1키
	void SetCameraThirdMode();// 숫자 2키
	void SetCameraTopViewMode();// 숫자 3키


	//사용안함.
	//UCameraComponent* GetFollowCamera();

	ECameraMode CurrentMode;
	//ECameraMode PrevCameraMode = ECameraMode::TopViewMode;

	void OnCameraModeChanged(const ECameraMode newCameraMode, const ECameraMode previousCameraMode);

	UFUNCTION(BlueprintCallable)
	virtual void ToggleCCTVTargetWithBlend(AActor* NewViewTarget, FRotator NewControlRotation, float BlendTime, EViewTargetBlendFunction BlendFunc, float BlendExp, bool bLockOutgoing);


private:
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
