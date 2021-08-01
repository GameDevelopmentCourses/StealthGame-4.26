// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Camera/CameraComponent.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"

#include "AIGard_Real.generated.h"

UENUM(BlueprintType)
enum class EAIState:uint8
{
   Idle,

   Suspicious,

   Alerted
	
};

//class UPawnSensingComponent;
UCLASS()
class FPSGAME_API AAIGard_Real : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIGard_Real();
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Orignal Direction In which Guard Was Looking
	FRotator OrignalRotation;

	FTimerHandle TimerHandle_ResetTime;

	EAIState GuardState;
	void SetGuardState(EAIState NewState);

	//AI perseption for seeing and listening
	UPROPERTY(VisibleAnywhere,Category="AI")
	UPawnSensingComponent * PawnSensingComp;

	UPROPERTY(EditInstanceOnly,BlueprintReadWrite,Category="AI")
	float WaitTime=10;

    UPROPERTY(EditInstanceOnly,Category="AI")
	bool bPatrol;

	UPROPERTY(EditInstanceOnly,BlueprintReadWrite,Category="AI")
	ATargetPoint* Target0;

	UPROPERTY(EditInstanceOnly,BlueprintReadWrite,Category="AI")
	ATargetPoint* Target1;

	ATargetPoint* GuardMovePoint;
	
	//Custom Function for Sceeing the actor
	UFUNCTION()
	void OnPawnSeen(APawn* SceenPawn);
	//Custom Function For Noice Heard
	UFUNCTION()
	void OnNoiceHeard(APawn* NewInstigator, const FVector& Location, float Volume);

	//Timer after whose end The Guard Will Reset to Original Rotation Values 
	UFUNCTION()
    void ResetTimerFunction();

	UFUNCTION()
	void MoveGaurdToLocation(float DelayTime);
	
	UFUNCTION(BlueprintImplementableEvent,Category="AI")
	void OnStateChange(EAIState NewState);

	
	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};



