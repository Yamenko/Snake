// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZoneConstructor.generated.h"

class AFloor;
class AWall;

UCLASS()
class SNAKE_API AZoneConstructor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZoneConstructor();
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//------------------------------------------
	//			 ZONE PROPORTIONS
	//------------------------------------------
	UPROPERTY(EditAnywhere)
	int32 Column;

	UPROPERTY(EditAnywhere)
	int32 Row;

	UPROPERTY(EditAnywhere)
	float Padding;

	//------------------------------------------
	//			 ZONE COMPONENTS
	//------------------------------------------
	UPROPERTY()
	UStaticMeshComponent* MyRootComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWall> WallComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFloor> FloorComponent;

	UPROPERTY()
	TArray<AWall*>WallElements;

	UPROPERTY()
	TArray<AFloor*>FloorElements;

};
