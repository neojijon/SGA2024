// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCameraManager.h"


void AMyPlayerCameraManager::SetCameraMode(ECameraMode newCameraMode)
{
	switch (CameraMode)
	{
	case TopViewMode:
		RemoveCameraModifier(FindCameraModifierByClass(TopViewCameraModifier));
		break;
	case ThirdPersonMode:
		RemoveCameraModifier(FindCameraModifierByClass(ThirdPersonCameraModifier));
		break;
	case FirstPersonMode:
		RemoveCameraModifier(FindCameraModifierByClass(FirstPersonCameraModifier));
		break;
	case CCTVMode:
		RemoveCameraModifier(FindCameraModifierByClass(CCTVCameraModifier));
		break;
	default:
		break;
	}

	PreviousCameraMode = CameraMode;
	CameraMode = newCameraMode;

	switch (CameraMode)
	{
	case TopViewMode:
		AddNewCameraModifier(TopViewCameraModifier);
		break;
	case ThirdPersonMode:
		AddNewCameraModifier(ThirdPersonCameraModifier);
		break;
	case FirstPersonMode:
		AddNewCameraModifier(FirstPersonCameraModifier);
		break;
	default:
		AddNewCameraModifier(CCTVCameraModifier);
		break;
	}
}