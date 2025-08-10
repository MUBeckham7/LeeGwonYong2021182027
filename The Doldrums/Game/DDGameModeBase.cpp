// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DDGameModeBase.h"
#include "GameFramework/PlayerState.h"       
#include "GameFramework/PlayerController.h"    
#include "GameFramework/PlayerState.h"


ADDGameModeBase::ADDGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn>DefaultPawnClassRef(TEXT("/Game/BluePrint/Character/BP_DDCharacterPlayer.BP_DDCharacterPlayer_C"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}


	//DefaultPawnClass

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Game/BluePrint/Character/BP_PlayerController.BP_PlayerController_C"));
	if (PlayerControllerClassRef.Class) 
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
	///Script/TheDoldrums.DDPlayerController


	static ConstructorHelpers::FClassFinder<APlayerState> PlayerStateClassRef(TEXT("/Game/BluePrint/Character/BP_DDPlayerState.BP_DDPlayerState_C"));
	if (PlayerStateClassRef.Class)
	{
		PlayerStateClass = PlayerStateClassRef.Class;
	}

}
