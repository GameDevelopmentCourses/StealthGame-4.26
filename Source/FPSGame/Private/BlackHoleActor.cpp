// Fill out your copyright notice in the Description page of Project Settings.
#include "BlackHoleActor.h"

#include "FPSCharacter.h"
#include "Components/SphereComponent.h"



// Sets default values
ABlackHoleActor::ABlackHoleActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	DestroySphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("DestroySphereComp"));
	DestroySphereComp->SetupAttachment(MeshComp);
	
	
	AttractSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("AttractSphereComp"));
	AttractSphereComp->SetupAttachment(MeshComp);

	DestroySphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DestroySphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	DestroySphereComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);



	

}


void ABlackHoleActor::DestroySphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1,10,FColor::Green,TEXT("enterd box destroy function"));
	//Destroy All Actor That Collides 
	if(OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called when the game starts or when spawned
void ABlackHoleActor::BeginPlay()
{
	Super::BeginPlay();
	DestroySphereComp->OnComponentBeginOverlap.AddDynamic(this,&ABlackHoleActor::DestroySphereOverlap);
}

// Called every frame
void ABlackHoleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    RadialForceApply();
}


void ABlackHoleActor::RadialForceApply()
{
	TArray<UPrimitiveComponent*> OverlappingComponent;
	AttractSphereComp->GetOverlappingComponents(OverlappingComponent);
	for(int i=0; i<OverlappingComponent.Num() ;i++)
	{
		UPrimitiveComponent*PrimComp=OverlappingComponent[i];
		if(PrimComp&&PrimComp->IsSimulatingPhysics())
		{
			//UE_LOG(LogTemp,Display,TEXT("code owrking"));
			
			const float RadiusOfAttraction =AttractSphereComp->GetUnscaledSphereRadius();
			const float StrengthOfAttraction =-2000;
			PrimComp->AddRadialForce(GetActorLocation(),RadiusOfAttraction,StrengthOfAttraction,ERadialImpulseFalloff::RIF_Constant,true);
		}
	}
}
