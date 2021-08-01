// Fill out your copyright notice in the Description page of Project Settings.
// this is going to be like a box where the player can get inside 
#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Actor.h"
#include "ExtractionZone.generated.h"

UCLASS()
class FPSGAME_API AExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExtractionZone();

protected:    
    UPROPERTY(VisibleAnywhere,Category="Component")
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere,Category="Component")
	UDecalComponent* DecalComp;
	UFUNCTION(BlueprintCallable,Category="MyFunction")
	void OnBoxTrigger(UPrimitiveComponent* OverlappedComponent,
		AActor*OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &SweepResult);
   
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
