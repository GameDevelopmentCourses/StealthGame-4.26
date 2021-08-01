// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"

#include "AITypes.h"
#include "FPSCharacter.h"
#include "Components/DecalComponent.h"
#include "kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ALaunchPad::ALaunchPad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Empty Scene Component
	EmptySceneComp =CreateDefaultSubobject<USceneComponent>(TEXT("EmptySceneComponenet"));
    RootComponent= EmptySceneComp;
	
	//Actual Mesh for Launch Pad
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComp->SetupAttachment(EmptySceneComp);

	//Direction Arrow Stricker
	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
    DecalComp->SetupAttachment(EmptySceneComp);

	//Box Collider

	BoxComp =CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComp->SetupAttachment(EmptySceneComp);

	//sepearting out when the player collides 
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	
	LaunchParticle=CreateDefaultSubobject<UParticleSystem>(TEXT("Launch Particle"));

	
}

void ALaunchPad::LaunchOnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,TEXT("inside collision"));

	AFPSCharacter* CollidingActor = Cast<AFPSCharacter>(OtherActor);
	//Checking if the player has collided
	FVector LaunchVelocity(0, 0, 1000);


	if (CollidingActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black,TEXT("box colided"));
		CollidingActor->LaunchCharacter(LaunchVelocity, false, true);
		UGameplayStatics::SpawnEmitterAtLocation(this, LaunchParticle, GetActorLocation());
	}

	// Launching box 
	if (OverlappedComponent)
	{
		
	}
}


// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();
	BoxComp->OnComponentBeginOverlap.AddDynamic(this,&ALaunchPad::LaunchOnCollision);
}

// Called every frame
void ALaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

