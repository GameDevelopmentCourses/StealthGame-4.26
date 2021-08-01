// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtractionZone.h"
#include "FPSCharacter.h"
#include "GameFramework/GameMode.h"
#include "FPSGameMode.h"

// Sets default values
AExtractionZone::AExtractionZone()
{
 	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	//Defining Box Component
	//
	//Setting it up as Root Component
	BoxComp =CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent=BoxComp;

	//Set Up Collision
	//
	//Collision to Query Only
	//Ignore Collision From All Channels
	//Allow Pawn To Generate Overlap Event
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);

    //Size Of Box Component
	BoxComp->SetBoxExtent(FVector(200.0f,200.0f,200.0f));

	//On collision call self defined function
	BoxComp->OnComponentBeginOverlap.AddDynamic(this,&AExtractionZone::OnBoxTrigger);

	//Decal Component allows you to Add Meshes
	//Determines how does the box looks 
    DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize =FVector(200.0f,200.0f,200.0f);
	DecalComp->SetupAttachment(RootComponent);
}

void AExtractionZone::OnBoxTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
    AFPSCharacter *MyPawn= Cast<AFPSCharacter>(OtherActor);
	if(MyPawn && MyPawn->bIsCarringObjective)
	{
        AFPSGameMode *MyGameMode =Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if(MyGameMode)
		{
			MyGameMode->CompletGame(MyPawn,true);
		}
	}
    
}

// Called when the game starts or when spawned
void AExtractionZone::BeginPlay()
{
	//super means using the default functionality of the begin play
	//ad we can add more custom work in this function
	Super::BeginPlay();
}

// Called every frame
void AExtractionZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

