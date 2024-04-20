// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSnakeElement.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "BaseSnake.h"


// Sets default values
ABaseSnakeElement::ABaseSnakeElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	MeshComponent->SetVisibility(false, true);
}

// Called when the game starts or when spawned
void ABaseSnakeElement::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ABaseSnakeElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseSnakeElement::SetFirstElementType_Implementation()
{
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseSnakeElement::HandleBeginOverlap);
	MeshComponent->SetVisibility(true, true);
}

void ABaseSnakeElement::Interact(AActor* Interactor, bool bIsHead)
{
	auto Snake = Cast<ABaseSnake>(Interactor);
	if (IsValid(Snake))
	{
		Snake->Destroy();
	}
}

void ABaseSnakeElement::HandleBeginOverlap(
	UPrimitiveComponent* OverlapComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if(IsValid(SnakeOwner))
	{
		SnakeOwner->SnakeElementOverlap(this, OtherActor);
	}
}

void ABaseSnakeElement::ToggleCollision()
{
	if (MeshComponent->GetCollisionEnabled() == ECollisionEnabled::NoCollision) {
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

