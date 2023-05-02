// Fill out your copyright notice in the Description page of Project Settings.


#include "BTGameMode.h"

ABTGameMode::ABTGameMode()
	:
	AGameMode()
{
	PlayerControllerClass = ABTPlayerController::StaticClass();
	DefaultPawnClass = ABTCharacter::StaticClass();

}