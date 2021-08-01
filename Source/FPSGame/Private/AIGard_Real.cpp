// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGard_Real.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"
#include "IMessageTracer.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

float InitialTime = 0;

// Sets default values
AAIGard_Real::AAIGard_Real()
{
	// Set this character to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	
	//Creat Pawn Sensing Component
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
}

// Called when the game starts or when spawned
void AAIGard_Real::BeginPlay()
{
	Super::BeginPlay();	

	//Describing Custom function for on PawnSee and PawnNoise
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIGard_Real::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AAIGard_Real::OnNoiceHeard);
	if(bPatrol)
	{
		MoveGaurdToLocation(WaitTime);
	}

	OrignalRotation = GetActorRotation();
}
// Called every frame
void AAIGard_Real::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(GuardMovePoint)
	{
		FVector DiffrenceDistance = GetActorLocation()-GuardMovePoint->GetActorLocation();

		float DistanceTOGoal= DiffrenceDistance.Size();

		if(DistanceTOGoal<50)
		{
		  MoveGaurdToLocation(WaitTime);	
		}
	}
	

}



void AAIGard_Real::OnPawnSeen(APawn* SceenPawn)
{
	//Show where The Ball Detected 
	DrawDebugSphere(GetWorld(), SceenPawn->GetActorLocation(), 32, 12, FColor::Green, false, 10);

	AFPSGameMode* MyGameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (MyGameMode)
	{
		MyGameMode->CompletGame(SceenPawn, false);
	}

	SetGuardState(EAIState::Alerted);
}

void AAIGard_Real::OnNoiceHeard(APawn* NewInstigator, const FVector& Location, float Volume)
{
	if (GuardState == EAIState::Alerted)
	{
		return;
	}

	DrawDebugSphere(GetWorld(), Location, 32, 12, FColor::Red, false, 10);

	//Get Direction of Rotation Between Place where Noise Is Heard
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookDirection = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookDirection.Pitch = 0;
	NewLookDirection.Roll = 0;

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetTime);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetTime, this, &AAIGard_Real::ResetTimerFunction, 3.0f);


	SetActorRotation(NewLookDirection);
	SetGuardState(EAIState::Suspicious);
}

void AAIGard_Real::ResetTimerFunction()
{
	if (GuardState == EAIState::Alerted)
	{
		return;
	}
	SetGuardState(EAIState::Idle);
	SetActorRotation(OrignalRotation);
}

void AAIGard_Real::MoveGaurdToLocation(float DelayTime)
{
	if(GuardMovePoint==nullptr || GuardMovePoint==Target0)
	{
	    GuardMovePoint=Target1;
		/*UE_LOG(LogTemp,Warning,TEXT("Actor Location: %s"),*GetActorLocation().ToString());
		UE_LOG(LogTemp,Warning,TEXT("Target0 Location: %s"),*Target0->GetActorLocation().ToString());
		*/
	}
	else
	{
		GuardMovePoint=Target0;
	}
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(),GuardMovePoint->GetActorLocation());
}


void AAIGard_Real::SetGuardState(EAIState NewState)
{
	if (GuardState == NewState)
	{
		return;
	}

	GuardState = NewState;
	OnStateChange(GuardState);
}

