
#include "ZoneConstructor.h"
#include  "Wall.h"
#include "Floor.h"
#include "Algo/Transform.h"

// Sets default values
AZoneConstructor::AZoneConstructor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MyRootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	SetRootComponent(MyRootComponent);

	Column	= 10;
	Row		= 6;
	Padding	= 100;
}

void AZoneConstructor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	TArray<USceneComponent*>TmpArr = MyRootComponent->GetAttachChildren();
	for (auto el : TmpArr)
	{
		//el->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		el->DestroyComponent();
	}
	TmpArr.Empty();

	//for (auto el : FloorElements){
	//	el->Destroy();
	//}
	

	FVector BaseLocation = Transform.GetLocation();
	for (int32 i = 1; i < Column; ++i){
		BaseLocation.X += Padding;
		FTransform TmpTransform(BaseLocation);
		AFloor* NewFloorElement = GetWorld()->SpawnActor<AFloor>(FloorComponent, TmpTransform);
		NewFloorElement->AttachToComponent(MyRootComponent, FAttachmentTransformRules::KeepWorldTransform);
		//FloorElements.Add(NewFloorElement);
		//NewFloorElement->Destroy();
	}
}

// Called when the game starts or when spawned
void AZoneConstructor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZoneConstructor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

