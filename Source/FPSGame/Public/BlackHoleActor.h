// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHoleActor.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API ABlackHoleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackHoleActor();

protected:
	UPROPERTY(VisibleAnywhere,Category = "Component")
	UMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category = "Component")
	USphereComponent* DestroySphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite , Category = "Component")
	USphereComponent* AttractSphereComp;

	UFUNCTION()
	void DestroySphereOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void RadialForceApply();
};


