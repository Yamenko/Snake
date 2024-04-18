// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSnake.generated.h"

class ABaseSnakeElement;

UENUM()
enum class EMovementDirection { UP, DOWN, LEFT, RIGHT};


UCLASS()
class SNAKE_API ABaseSnake : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSnake();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseSnakeElement> SnakeElementClass;

	UPROPERTY(EditDefaultsOnly)
	float ElementSize;
	UPROPERTY()
	TArray<ABaseSnakeElement*>SnakeElements;

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed;

	UPROPERTY()
	EMovementDirection LastMoveDirection;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AddSnakeElement(int Elements = 1);
	UFUNCTION(BlueprintCallable)
	void Move();
	bool CanChangeDirection;

	UFUNCTION()
	void SnakeElementOverlap(ABaseSnakeElement* OverlapedElement, AActor* Other);

	
};
