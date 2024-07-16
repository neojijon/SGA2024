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

//��������Ʈ ���� ECameraMode Ÿ���� newCameraMode�� oldCameraMode��� �� ���� �Ķ���͸� �޽��ϴ�.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCameraModeChangedSignature, ECameraMode, newCameraMode, ECameraMode, oldCameraMode);

UCLASS()
class SGA2024_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()


public:	
	AMyPlayerController(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


	//�÷��̾� ī�޶� �޴��� �ʱ�ȭ���ִ� ����
	virtual void SpawnPlayerCameraManager() override;

	//Pawn 
	virtual void OnPossess(APawn* InPawn) override;

	// ��������Ʈ �ν��Ͻ�
	UPROPERTY(BlueprintAssignable, Category = PlayerController)
	FOnCameraModeChangedSignature OnCameraModeChangedDelegate;


protected:
	TWeakObjectPtr<AMyPlayerCameraManager> _MyPlayerCameraManager;


public:

	void SwapCameraMode();
	void SwitchCameraMode(); //TabŰ

	ECameraMode GetCameraMode();

	void SetCameraFirstMode();// ���� 1Ű
	void SetCameraThirdMode();// ���� 2Ű
	void SetCameraTopViewMode();// ���� 3Ű


	//������.
	//UCameraComponent* GetFollowCamera();

	ECameraMode CurrentMode;
	//ECameraMode PrevCameraMode = ECameraMode::TopViewMode;

	void OnCameraModeChanged(const ECameraMode newCameraMode, const ECameraMode previousCameraMode);

	UFUNCTION(BlueprintCallable)
	virtual void ToggleCCTVTargetWithBlend(AActor* NewViewTarget, FRotator NewControlRotation, float BlendTime, EViewTargetBlendFunction BlendFunc, float BlendExp, bool bLockOutgoing);


private:
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
