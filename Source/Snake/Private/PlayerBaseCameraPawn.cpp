// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBaseCameraPawn.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "./BaseSnake.h"

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

}

void APlayerBaseCameraPawn::CreateSnakeActor()
{
	BaseSnake = GetWorld()->SpawnActor<ABaseSnake>(BaseSnakeClass, FTransform());
}

