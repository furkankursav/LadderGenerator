// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralLadder.h"
#include "Components/BoxComponent.h"

// Sets default values
AProceduralLadder::AProceduralLadder()
{
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = DefaultSceneRoot;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(GetRootComponent());


	LadderBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LadderBase"));
	LadderBase->SetupAttachment(GetRootComponent());


	MiddleParts = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Middles"));
	MiddleParts->SetupAttachment(LadderBase);

	if (TopLadderMesh == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Tmp_TopLadderMesh(TEXT(
			"StaticMesh'/Game/ProceduralLadderGenerator/Meshes/DefaultLadder/SM_DefautlLadder_Top.SM_DefautlLadder_Top'"));
		TopLadderMesh = Tmp_TopLadderMesh.Object;
	}

	if (MidLadderMesh == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Tmp_MidLadderMesh(TEXT(
			"StaticMesh'/Game/ProceduralLadderGenerator/Meshes/DefaultLadder/SM_DefaultLadder_Middle.SM_DefaultLadder_Middle'"));
		TopLadderMesh = Tmp_MidLadderMesh.Object;
	}
}


void AProceduralLadder::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (TopLadderMesh != nullptr && MidLadderMesh != nullptr)
	{
		if (LadderBase != nullptr)
		{
			LadderBase->SetStaticMesh(TopLadderMesh);
		}

		if (MidLadderMesh != nullptr)
		{
			MiddleParts->SetStaticMesh(MidLadderMesh);
		}

		MiddleParts->ClearInstances();

		for (int i = 0; i < MidPartCount; i++)
		{
			FTransform InstanceTransform(FVector(0.0f, 0.0f, MidLadderMesh->GetBoundingBox().GetSize().Z * -1.f * i));
			MiddleParts->AddInstance(InstanceTransform);
		}

		FVector BoxExtent;
		BoxExtent.X = TopLadderMesh->GetBoundingBox().GetSize().X / 2;
		BoxExtent.Y = TopLadderMesh->GetBoundingBox().GetSize().Y / 2;

		FVector BoxLocation;
		BoxLocation.X = 0.f;
		BoxLocation.Y = 0.f;

		const float MeshHeights = TopLadderMesh->GetBoundingBox().GetSize().Z + MidLadderMesh->GetBoundingBox().
			GetSize().Z * MidPartCount;

		BoxExtent.Z = MeshHeights * 0.5f + TopOffset;
		BoxLocation.Z = -BoxExtent.Z + TopLadderMesh->GetBoundingBox().GetSize().Z + 2.f * TopOffset;


		BoxCollision->SetBoxExtent(BoxExtent, true);
		BoxCollision->SetRelativeLocation(BoxLocation);
	}
}
