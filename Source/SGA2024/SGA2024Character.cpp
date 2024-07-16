// Copyright Epic Games, Inc. All Rights Reserved.

#include "SGA2024Character.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "MyPlayerController.h"
#include "MyPlayerCameraManager.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ASGA2024Character

ASGA2024Character::ASGA2024Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ASGA2024Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}


//캐릭터가 새로운 컨트롤러에 의해 소유될 때 호출됩니다. 
void ASGA2024Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	_MyPlayerController = Cast<AMyPlayerController>(Controller);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASGA2024Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASGA2024Character::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASGA2024Character::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ASGA2024Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (_MyPlayerController.IsValid())
	{
		if (_MyPlayerController.Get()->GetCameraMode() == ThirdPersonMode)
		{
			MoveThirdPerson(MovementVector);
			return;
		}

		if (_MyPlayerController.Get()->GetCameraMode() == TopViewMode)
		{
			MoveTopDown(MovementVector);
			return;
		}

		if (_MyPlayerController.Get()->GetCameraMode() == FirstPersonMode)
		{
			MoveFirstPerson(MovementVector);
			return;
		}
	}

	// Todo Make sure to maintain the control rotation when we change the camera point of view until we release the moving input. 
	MoveTopDown(MovementVector);


	//if (Controller != nullptr)
	//{
	//	// find out which way is forward
	//	const FRotator Rotation = Controller->GetControlRotation();
	//	const FRotator YawRotation(0, Rotation.Yaw, 0);

	//	// get forward vector
	//	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//
	//	// get right vector 
	//	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//	// add movement 
	//	AddMovementInput(ForwardDirection, MovementVector.Y);
	//	AddMovementInput(RightDirection, MovementVector.X);
	//}
}

void ASGA2024Character::MoveTopDown(const FVector2D& movementVector)
{
	if (Controller != nullptr)
	{
		// add movement, Todo replace unit vectors with an arbitrary direction once it's changed per map
		AddMovementInput(FVector::UnitX(), movementVector.Y);
		AddMovementInput(FVector::UnitY(), movementVector.X);
	}
}


void ASGA2024Character::MoveFirstPerson(const FVector2D& movementVector)
{
	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), movementVector.Y);
		AddMovementInput(GetActorRightVector(), movementVector.X);
	}
}

void ASGA2024Character::MoveThirdPerson(const FVector2D& movementVector)
{
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, movementVector.Y);
		AddMovementInput(RightDirection, movementVector.X);
	}
}


void ASGA2024Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (_MyPlayerController.IsValid())
		{
			if ( (_MyPlayerController.Get()->GetCameraMode() == FirstPersonMode) ||
				 (_MyPlayerController.Get()->GetCameraMode() == ThirdPersonMode) )
			{

				// add yaw and pitch input to controller
				AddControllerYawInput(LookAxisVector.X);
				AddControllerPitchInput(LookAxisVector.Y);
			}
		}
	}
}