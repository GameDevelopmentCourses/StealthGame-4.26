// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

UCLASS()
class FPSGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	// Called when the game starts or when spawned

	UPROPERTY(VisibleAnywhere,Category="Component")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere,Category="Component")
	UDecalComponent* DecalComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Component")
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Component")
	USceneComponent* EmptySceneComp;
	
	UPROPERTY(EditDefaultsOnly,Category="Effects")
	UParticleSystem* LaunchParticle;

	
    UFUNCTION()
	void LaunchOnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
