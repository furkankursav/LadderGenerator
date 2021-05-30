// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Ladder.generated.h"

UCLASS()
class LADDERGENERATOR_API ALadder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALadder();
	UPROPERTY(VisibleAnywhere)
		USceneComponent* SceneRoot;
	UPROPERTY()
		UStaticMeshComponent* LadderBase;

	UPROPERTY(EditAnywhere, Category = "Ladder Generator")
		UStaticMesh* TopLadderMesh;
	UPROPERTY(EditAnywhere, Category = "Ladder Generator")
		UStaticMesh* MidLadderMesh;
	UPROPERTY(EditAnywhere, Category = "Ladder Generator")
		int LadderHeight;
	UPROPERTY()
		UInstancedStaticMeshComponent* middles;
	UPROPERTY()
		UBoxComponent* BoxCollision;

	UFUNCTION()
		void OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnBoxCollisionEndOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	virtual void PostEditChangeProperty
	(
		FPropertyChangedEvent& PropertyChangedEvent
	) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
