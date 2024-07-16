// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "SGA2024Character.h"


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

	CameraMode = ECameraMode::ThirdMode;

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


void AMyPlayerController::SwitchCameraMode()
{
	UE_LOG(LogTemp, Warning, TEXT("SwitchCameraMode Select"));

	switch (CameraMode)
	{
	case FirstMode:		
		SetCameraThirdMode();
		break;
	case  ThirdMode:		
		SetCameraTopViewMode();
		break;
	case TopView:		
		SetCameraFirstMode();
		break;
	}
}

void AMyPlayerController::SetCameraFirstMode()
{
	CameraMode = ECameraMode::FirstMode;

	UCameraComponent*  pCamera = GetFollowCamera();
	if(pCamera)
	{
		pCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
		pCamera->SetRelativeRotation(FRotator::ZeroRotator);

		UE_LOG(LogTemp, Warning, TEXT("SetCameraFirstMode"));
	}
}

void AMyPlayerController::SetCameraThirdMode()
{
	CameraMode = ECameraMode::ThirdMode;

	UCameraComponent* pCamera = GetFollowCamera();
	if (pCamera)
	{
		pCamera->SetRelativeLocation(FVector(-300.0f, 0.0f, 50.0f));
		pCamera->SetRelativeRotation(FRotator::ZeroRotator);

		UE_LOG(LogTemp, Warning, TEXT("SetCameraThirdMode"));
	}
}

void AMyPlayerController::SetCameraTopViewMode()
{
	CameraMode = ECameraMode::TopView;

	UCameraComponent* pCamera = GetFollowCamera();
	if (pCamera)
	{
		pCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 500.0f));
		pCamera->SetRelativeRotation(FRotator(-90.0f,0.0f,0.0f));

		UE_LOG(LogTemp, Warning, TEXT("SetCameraTopViewMode"));
	}
}

UCameraComponent* AMyPlayerController::GetFollowCamera()
{
	ASGA2024Character *pCharacter = Cast<ASGA2024Character>(GetCharacter());

	if (pCharacter)
	{
		return pCharacter->GetFollowCamera();
	}

	return nullptr;
}


