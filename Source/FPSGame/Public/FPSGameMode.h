// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
   UPROPERTY(EditDefaultsOnly,Category="StaticObjectClass")
   TSubclassOf<AActor> MyNewPosition;
public:

	AFPSGameMode();
	
	void CompletGame(APawn* MyPawn,bool bMissionSucess);

	UFUNCTION(BlueprintImplementableEvent,Category="Game Mode")
	void OnMissionComplete(APawn* MyPawn,bool bMissionSucess);
};



