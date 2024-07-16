// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "SGA2024Character.h"
#include "MyPlayerCameraManager.h"


AMyPlayerController::AMyPlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{	
	
	PlayerCameraManagerClass = AMyPlayerController::StaticClass();
}


void AMyPlayerController::BeginPlay()
{
	
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(this))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Camera, 1);
		}
	}

	//CameraMode = ECameraMode::ThirdMode;

}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(IA_CameraChangeMode, ETriggerEvent::Triggered, this, &AMyPlayerController::SwitchCameraMode);
		EnhancedInputComponent->BindAction(IA_FirstMode, ETriggerEvent::Triggered, this, &AMyPlayerController::SetCameraFirstMode);
		EnhancedInputComponent->BindAction(IA_ThirdMode, ETriggerEvent::Triggered, this, &AMyPlayerController::SetCameraThirdMode);
		EnhancedInputComponent->BindAction(IA_TopView, ETriggerEvent::Triggered, this, &AMyPlayerController::SetCameraTopViewMode);
	}

}

void AMyPlayerController::SpawnPlayerCameraManager()
{
	Super::SpawnPlayerCameraManager();

	_MyPlayerCameraManager = Cast <AMyPlayerCameraManager>(PlayerCameraManager);
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (_MyPlayerCameraManager.IsValid())
	{
		_MyPlayerCameraManager.Get()->SetCameraMode(TopViewMode);
	}
}


void AMyPlayerController::SwapCameraMode()
{
	if (_MyPlayerCameraManager.IsValid())
	{
		if (_MyPlayerCameraManager->GetCameraMode() != CCTVMode)
		{
			// Done this way so it's open to multiple Camera Modes
			CurrentMode = _MyPlayerCameraManager.Get()->GetCameraMode();
			switch (CurrentMode)
			{
			case FirstPersonMode:
				CurrentMode = ThirdPersonMode;
				break;
			case  ThirdPersonMode:
				CurrentMode = TopViewMode;
				break;
			case TopViewMode:
				CurrentMode = FirstPersonMode;
				break;
			}

			_MyPlayerCameraManager.Get()->SetCameraMode(CurrentMode);
		}
	}
}

void AMyPlayerController::SwitchCameraMode()
{
	UE_LOG(LogTemp, Warning, TEXT("SwitchCameraMode Select"));

	if (_MyPlayerCameraManager.IsValid())
	{
		CurrentMode = GetCameraMode();

		if (CurrentMode != CCTVMode)
		{	
			switch (CurrentMode)
			{
			case FirstPersonMode:
				CurrentMode = ThirdPersonMode;
				break;
			case  ThirdPersonMode:
				CurrentMode = TopViewMode;
				break;
			case TopViewMode:
				CurrentMode = FirstPersonMode;
				break;
			}

			_MyPlayerCameraManager.Get()->SetCameraMode(CurrentMode);
		}
	}
}

ECameraMode AMyPlayerController::GetCameraMode()
{
	if (_MyPlayerCameraManager.IsValid())
	{
		return _MyPlayerCameraManager.Get()->GetCameraMode();
	}

	return Default;
}


void AMyPlayerController::SetCameraFirstMode()
{
	if (_MyPlayerCameraManager.IsValid())
	{
		if (GetCameraMode() != CCTVMode)
		{
			CurrentMode = ECameraMode::FirstPersonMode;
			_MyPlayerCameraManager.Get()->SetCameraMode(CurrentMode);
		}
	}

	/*UCameraComponent*  pCamera = GetFollowCamera();
	if(pCamera)
	{
		pCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
		pCamera->SetRelativeRotation(FRotator::ZeroRotator);

		UE_LOG(LogTemp, Warning, TEXT("SetCameraFirstMode"));
	}*/
}

void AMyPlayerController::SetCameraThirdMode()
{

	if (_MyPlayerCameraManager.IsValid())
	{
		if (GetCameraMode() != CCTVMode)
		{
			CurrentMode = ECameraMode::ThirdPersonMode;
			_MyPlayerCameraManager.Get()->SetCameraMode(CurrentMode);
		}
	}

	/*
	CurrentMode = ECameraMode::ThirdPersonMode;

	UCameraComponent* pCamera = GetFollowCamera();
	if (pCamera)
	{
		pCamera->SetRelativeLocation(FVector(-300.0f, 0.0f, 50.0f));
		pCamera->SetRelativeRotation(FRotator::ZeroRotator);

		UE_LOG(LogTemp, Warning, TEXT("SetCameraThirdMode"));
	}
	*/
}

void AMyPlayerController::SetCameraTopViewMode()
{
	if (_MyPlayerCameraManager.IsValid())
	{
		if (GetCameraMode() != CCTVMode)
		{
			CurrentMode = ECameraMode::TopViewMode;
			_MyPlayerCameraManager.Get()->SetCameraMode(CurrentMode);
		}
	}


	/*
	CurrentMode = ECameraMode::TopViewMode;

	UCameraComponent* pCamera = GetFollowCamera();
	if (pCamera)
	{
		pCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 500.0f));
		pCamera->SetRelativeRotation(FRotator(-90.0f,0.0f,0.0f));

		UE_LOG(LogTemp, Warning, TEXT("SetCameraTopViewMode"));
	}
	*/
}

//UCameraComponent* AMyPlayerController::GetFollowCamera()
//{
//	ASGA2024Character *pCharacter = Cast<ASGA2024Character>(GetCharacter());
//
//	if (pCharacter)
//	{
//		return pCharacter->GetFollowCamera();
//	}
//
//	return nullptr;
//}

void AMyPlayerController::OnCameraModeChanged(const ECameraMode newCameraMode, const ECameraMode previousCameraMode)
{
	OnCameraModeChangedDelegate.Broadcast(newCameraMode, previousCameraMode);
}

void AMyPlayerController::ToggleCCTVTargetWithBlend(AActor* NewViewTarget, FRotator NewControlRotation, float BlendTime, EViewTargetBlendFunction BlendFunc, float BlendExp, bool bLockOutgoing)
{

	if (_MyPlayerCameraManager.IsValid())
	{
		const ECameraMode previousCameraMode = GetCameraMode();
		if (previousCameraMode == CCTVMode && NewViewTarget == GetPawn())
		{
			// Go back to the previous Camera Mode
			_MyPlayerCameraManager.Get()->SetCameraMode(_MyPlayerCameraManager.Get()->GetPreviousCameraMode());
			SetViewTargetWithBlend(NewViewTarget, BlendTime, BlendFunc, BlendExp, bLockOutgoing);
		}
		else
		{
			_MyPlayerCameraManager.Get()->SetCameraMode(CCTVMode);
			SetControlRotation(NewControlRotation);
			SetViewTargetWithBlend(NewViewTarget, BlendTime, BlendFunc, BlendExp, bLockOutgoing);
		}

		OnCameraModeChanged(GetCameraMode(), previousCameraMode);
	}
}



