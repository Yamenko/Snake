// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBaseCameraPawn.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "./BaseSnake.h"
#include "Components/InputComponent.h"

// Sets default values
APlayerBaseCameraPawn::APlayerBaseCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	RootComponent = PawnCamera;

}

// Called when the game starts or when spawned
void APlayerBaseCameraPawn::BeginPlay()
{
	Super::BeginPlay();

	SetActorRotation(FRotator(-90, 0, 0));
	CreateSnakeActor();
	
}

// Called every frame
void APlayerBaseCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerBaseCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerBaseCameraPawn::HandlePlayerVerticalInput);
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerBaseCameraPawn::HandlePlayerHorizontalInput);
}

void APlayerBaseCameraPawn::CreateSnakeActor()
{
	BaseSnake = GetWorld()->SpawnActor<ABaseSnake>(BaseSnakeClass, FTransform());
}

void APlayerBaseCameraPawn::HandlePlayerVerticalInput(float value)
{
	if (IsValid(BaseSnake)){
		if (value > 0 && BaseSnake->LastMoveDirection != EMovementDirection::DOWN){
			BaseSnake->LastMoveDirection = EMovementDirection::UP;
		}
		else if (value < 0 && BaseSnake->LastMoveDirection != EMovementDirection::UP)	{
			BaseSnake->LastMoveDirection = EMovementDirection::DOWN;
		}
	}
}

void APlayerBaseCameraPawn::HandlePlayerHorizontalInput(float value)
{
	if (IsValid(BaseSnake)) {
		if (value > 0 && BaseSnake->LastMoveDirection != EMovementDirection::LEFT) {
			BaseSnake->LastMoveDirection = EMovementDirection::RIGHT;
		}
		else if (value < 0 && BaseSnake->LastMoveDirection != EMovementDirection::RIGHT) {
			BaseSnake->LastMoveDirection = EMovementDirection::LEFT;
		}
	}
}


