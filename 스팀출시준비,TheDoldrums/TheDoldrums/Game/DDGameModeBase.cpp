// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DDGameModeBase.h"

ADDGameModeBase::ADDGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn>DefaultPawnClassRef(TEXT("/Script/TheDoldrums.DDCharacterPlayer"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}


	//DefaultPawnClass

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/TheDoldrums.DDPlayerController"));
	if (PlayerControllerClassRef.Class) 
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

}
