// Fill out your copyright notice in the Description page of Project Settings.

#include "PicupActor.h"
#include "Components/SphereComponent.h"
#include "kismet/GameplayStatics.h"
#include "FPSCharacter.h"

// Sets default values
APicupActor::APicupActor()
{
 	// Set this actor to call Tick() every frame. 
	PrimaryActorTick.bCanEverTick = true;

	//Mesh To Create PickUp Object
	//
	//SetUp To No Collision
	//Make it RootComponent
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	//Create Sphere Component for Collision Detection
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));

	//Set Up Collision
	//
	//Collision to Query Only
	//Ignore Collision From All Channels
	//Allow Pawn To Generate Overlap Event
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	//Attach SphereComp To MeshComponent
	SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void APicupActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APicupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APicupActor::PlayEffect()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, ParticleFx, GetActorLocation());
}

void APicupActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
    //Check FOr OverlappingActor To be PlayerCharacter
	if (MyCharacter)
	{
		MyCharacter->bIsCarringObjective = true;
		//Destroy self (so it seems like player has picked it up)
		Destroy();
	}

	//Play Particle Effect On entering the Sphere Trigger Area
	PlayEffect();
}

