// Copyright Furkan KURSAV

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralLadder.generated.h"

UCLASS()
class LADDERGENERATOR_API AProceduralLadder : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProceduralLadder();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ladder")
	class USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ladder")
	class UStaticMeshComponent* LadderBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ladder | Customize")
	class UStaticMesh* TopLadderMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ladder | Customize")
	class UStaticMesh* MidLadderMesh;

	UPROPERTY(EditAnywhere, Category = "Ladder | Customize",
		meta = (EditCondition="TopLadderMesh != nullptr && MidLadderMesh != nullptr", ClampMin="0", ClampMax="50"))
	int MidPartCount;

	UPROPERTY(EditAnywhere, Category = "Ladder | Customize", meta = (ClampMin="0", ClampMax="100"))
	float TopOffset = 20.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ladder")
	class UInstancedStaticMeshComponent* MiddleParts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ladder")
	class UBoxComponent* BoxCollision;


	virtual void OnConstruction(const FTransform& Transform) override;
};
