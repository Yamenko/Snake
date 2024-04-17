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
	LastMoveDirection = EMovementDirection::DOWN;

}

// Called when the game starts or when spawned
void ABaseSnake::BeginPlay()
{
	Super::BeginPlay();
	//GetWorld()->SpawnActor<ABaseSnakeElement>(SnakeElementClass, GetActorTransform());
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(4);
	
}

// Called every frame
void ABaseSnake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ABaseSnake::AddSnakeElement(int Elements)
{
	for (int i = 0; i < Elements; ++i) {
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform TmpTransform(NewLocation);
		ABaseSnakeElement* NewSnakeElements = GetWorld()->SpawnActor<ABaseSnakeElement>(SnakeElementClass, TmpTransform);
		//NewSnakeElements->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		int32 ElementIndex =  SnakeElements.Add(NewSnakeElements);

		if (ElementIndex == 0 )
		{
			NewSnakeElements->SetFirstElementType();

		}
	}
}

void ABaseSnake::Move()
{
	FVector MovementVector;
	float MSpeed = ElementSize;
	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += MSpeed;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= MSpeed;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += MSpeed;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y -= MSpeed;
		break;
	default: ;
	}

	//AddActorWorldOffset(MovementVector);

	for (int i = SnakeElements.Num() - 1; i > 0; --i)
	{
		auto CurentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurentElement->SetActorLocation(PrevLocation);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector); // Голова!

}

