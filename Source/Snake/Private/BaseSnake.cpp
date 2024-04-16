// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSnake.h"
#include "BaseSnakeElement.h"

// Sets default values
ABaseSnake::ABaseSnake()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ElementSize = 100.0f;
	MovementSpeed = 10.0f;
	LastMoveDirection = EMovementDirection::UP;

}

// Called when the game starts or when spawned
void ABaseSnake::BeginPlay()
{
	Super::BeginPlay();
	//GetWorld()->SpawnActor<ABaseSnakeElement>(SnakeElementClass, GetActorTransform());
	AddSnakeElement(4);
	
}

// Called every frame
void ABaseSnake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);

}

void ABaseSnake::AddSnakeElement(int Elements)
{
	for (int i = 0; i < Elements; ++i) {
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform TmpTransform(NewLocation);
		ABaseSnakeElement* NewSnakeElements = GetWorld()->SpawnActor<ABaseSnakeElement>(SnakeElementClass, TmpTransform);
		NewSnakeElements->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		SnakeElements.Add(NewSnakeElements);
	}
}

void ABaseSnake::Move(float DeltaTime)
{
	FVector MovementVector;
	float MovementDeltaSpeed = MovementSpeed * DeltaTime;

	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += MovementDeltaSpeed;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= MovementDeltaSpeed;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += MovementDeltaSpeed;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y -= MovementDeltaSpeed;
		break;
	default: ;
	}

	AddActorWorldOffset(MovementVector);
}

