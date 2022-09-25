// Copyright Epic Games, Inc. All Rights Reserved.


#include "RemnantsofthepastGameModeBase.h"
#include "Actors/Class_Character.h"
#include "Controllers/Class_PlayerController.h"
#include "UI/Class_HUD.h"

ARemnantsofthepastGameModeBase::ARemnantsofthepastGameModeBase()
{
	DefaultPawnClass = AClass_Character::StaticClass();
	PlayerControllerClass = AClass_PlayerController::StaticClass();
	HUDClass = AClass_HUD::StaticClass();
}
