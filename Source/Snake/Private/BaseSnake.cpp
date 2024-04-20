// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSnake.h"
#include "BaseSnakeElement.h"
#include "Interactable.h"

// Sets default values
ABaseSnake::ABaseSnake()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ElementSize = 35.0f;
	MovementSpeed = 5.0f;
	LastMoveDirection = EMovementDirection::DOWN;

}

// Called when the game starts or when spawned
void ABaseSnake::BeginPlay()
{
	Super::BeginPlay();
	//GetWorld()->SpawnActor<ABaseSnakeElement>(SnakeElementClass, GetActorTransform());
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(4);

	CanChangeDirection = true;
	
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
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0); // SnakeElements.Num()

		FTransform TmpTransform(NewLocation);
		ABaseSnakeElement* NewSnakeElements = GetWorld()->SpawnActor<ABaseSnakeElement>(SnakeElementClass, TmpTransform);
		int32 ElementIndex =  SnakeElements.Add(NewSnakeElements);

		NewSnakeElements->SnakeOwner = this;
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

	SnakeElements[0]->ToggleCollision();

	for (int i = SnakeElements.Num() - 1; i > 0; --i)
	{
		auto CurentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurentElement->SetActorLocation(PrevLocation);

		CurentElement->GetRootComponent()->SetVisibility(true, true);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector); // Голова!
	SnakeElements[0]->ToggleCollision();
	CanChangeDirection = true;
}

void ABaseSnake::SnakeElementOverlap(ABaseSnakeElement* OverlapedElement, AActor* Other)
{
	if (OverlapedElement)
	{
		int32 IndexElement;
		SnakeElements.Find(OverlapedElement, IndexElement);

		bool isHead = (IndexElement == 0);

		IInteractable* InteractableInterface = Cast<IInteractable>(Other);

		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, isHead);
		}
	}
}

