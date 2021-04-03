// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include  "PluProceduralBuilding/Interfases/I_GraphAction.h"
#include  "PluProceduralBuilding/Interfases/I_Node.h"
#include  "PluProceduralBuilding/Interfases/I_Branch.h"
#include  "PluProceduralBuilding/GraphElement/A_Graph_Node_Base.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Guid.h"
#include "AGraphCoreElement.generated.h"

UCLASS(Blueprintable)
class PLUPROCEDURALBUILDING_API AAGraphCoreElement : public AActor, public II_GraphAction
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAGraphCoreElement();
	virtual void OnConstruction(const FTransform& Transform) override;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SM;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<AActor*> TNodes;
	TArray<UStaticMeshComponent*>SMArray;
	TArray<USplineComponent*> SCArray;
	TMap<FGuid,FArrayConnectionType> DataConnectNode;
	void GetAllActorsLevel(TSubclassOf<UInterface> myInterfase,TArray<AActor*> &foundEnemies);
	void SearchNodesInTheWorld();
	void SearchBranches();
	void AddLineToBranch(FString NameComponent, FVector Start, FVector End, FVector RouteBranch);
	void AddStartEndDataToBranch(USplineComponent* Spline_, FVector Start, FVector End, FVector RouteBranch);
	void IGraphRebuildNodeSpace_Implementation() override;
	UFUNCTION(BlueprintCallable)
		void CRSp();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
