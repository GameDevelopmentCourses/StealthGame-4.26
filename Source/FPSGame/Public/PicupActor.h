// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PicupActor.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API APicupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Function To  Set Up default Object Or Values 
	APicupActor();

protected:
   //Mesh to create pickup object
	UPROPERTY(VisibleAnywhere,Category="Components")
	UMeshComponent* MeshComp;
	
   //Sphere for Collision Detection
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;
	
   //Particle System to Generate Particles
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ParticleFx;

	void PlayEffect();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//OverRide the Prebuild Function for OveralapingEvent
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
