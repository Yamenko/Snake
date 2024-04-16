// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSnakeElement.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"


// Sets default values
ABaseSnakeElement::ABaseSnakeElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
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

