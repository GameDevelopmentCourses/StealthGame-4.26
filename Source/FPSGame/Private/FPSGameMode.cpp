// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"



AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();


	//if actor overlap than disable the camera
	
}
void AFPSGameMode::CompletGame(APawn* InstigatePawn,bool bMissionSucess)
{
	if(InstigatePawn)
	{
		InstigatePawn->DisableInput(nullptr);
		TArray<AActor*> ActorList;
		UGameplayStatics::GetAllActorsOfClass(this,MyNewPosition,ActorList);

		AActor *EndCameraLocationActor=nullptr;
		if(ActorList.Num()>0)
		{
			EndCameraLocationActor =ActorList[0];		
		}
		else
		{
			UE_LOG(LogTemp,Error,TEXT("Actor List Not Set Up"))
		}

		APlayerController* NewController= Cast<APlayerController>(InstigatePawn->GetController());
		if(NewController)
		{
			NewController->SetViewTargetWithBlend(EndCameraLocationActor,1.05f,EViewTargetBlendFunction::VTBlend_Cubic);
		}
		else
		{
			UE_LOG(LogTemp,Error,TEXT("Blending Not Happening"));	
		}
		
		OnMissionComplete(InstigatePawn,bMissionSucess);
	}

	else
	{
		UE_LOG(LogTemp,Warning,TEXT("pawn has not arrived on the extraction zone"));
	}
	
}
