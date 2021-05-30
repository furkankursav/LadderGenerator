// Fill out your copyright notice in the Description page of Project Settings.


#include "Ladder.h"
#include "LadderGeneratorCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ALadder::ALadder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	
	LadderBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LadderBase"));
	LadderBase->SetupAttachment(SceneRoot);
	LadderBase->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->AttachToComponent(SceneRoot, FAttachmentTransformRules::KeepRelativeTransform);
	BoxCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ALadder::OnBoxCollisionBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ALadder::OnBoxCollisionEndOverlap);
	
	middles = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Middles"));
	middles->AttachToComponent(LadderBase, FAttachmentTransformRules::KeepRelativeTransform);
	middles->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

}

void ALadder::OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		ALadderGeneratorCharacter* MyCharacter = Cast<ALadderGeneratorCharacter>(OtherActor);
		MyCharacter->OnLadder = true;
		UCharacterMovementComponent* Hareket = MyCharacter->GetCharacterMovement();
		Hareket->SetMovementMode(EMovementMode::MOVE_Flying);
	}

}

void ALadder::OnBoxCollisionEndOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		ALadderGeneratorCharacter* MyCharacter = Cast<ALadderGeneratorCharacter>(OtherActor);
		MyCharacter->OnLadder = false;
		UCharacterMovementComponent* Hareket = MyCharacter->GetCharacterMovement();
		Hareket->SetMovementMode(EMovementMode::MOVE_Walking);

	}
}

void ALadder::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	
	

	

	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == "TopLadderMesh")
	{
		if (LadderBase != nullptr)
		{
			LadderBase->SetStaticMesh(TopLadderMesh);
			
			
		}
	}

	else if (PropertyName == "MidLadderMesh")
	{
		middles->SetStaticMesh(MidLadderMesh);
	}

	else if (PropertyName == "LadderHeight")
	{
		int LadderCount = LadderHeight / 100;
		middles->ClearInstances();
		BoxCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 200 + (-LadderHeight / 4)));
		BoxCollision->SetBoxExtent(FVector(64.0f, 32.0f, LadderHeight / 4 + 50), true);
		UE_LOG(LogTemp, Warning, TEXT("%d"), LadderCount);
		if (LadderBase != nullptr && MidLadderMesh != nullptr)
		{
			for (int i = 0; i < LadderCount; i++)
			{
				FTransform instanceTransform = FTransform(FVector(0.0f, 0.0f, i * 50.0f * -1.0f));
				middles->AddInstance(instanceTransform);
			}
		}
		
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);

}

// Called when the game starts or when spawned
void ALadder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALadder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

