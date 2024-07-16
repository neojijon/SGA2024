// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "SGA2024Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class AMyPlayerController;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ASGA2024Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	ASGA2024Character();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	//모드에 따른 움직임 제한
	void MoveTopDown(const FVector2D& movementVector);

	void MoveThirdPerson(const FVector2D& movementVector);

	void MoveFirstPerson(const FVector2D& movementVector);


	/** Called for looking input */
	void Look(const FInputActionValue& Value);
		
protected:
	TWeakObjectPtr<AMyPlayerController> _MyPlayerController;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void PossessedBy(AController* NewController) override;

//public:
//	/** Returns CameraBoom subobject **/
//	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
//	/** Returns FollowCamera subobject **/
//	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

