// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include "BaseSnake.h" 

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWall::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ABaseSnake>(Interactor);
		if (IsValid(Snake))
		{
			Snake->Destroy();
		}
	}
}

