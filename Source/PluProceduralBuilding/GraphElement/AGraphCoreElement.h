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
#include "ProceduralMeshComponent.h"
#include "earcut/earcut.h"
#include <array>
#include "AGraphCoreElement.generated.h"

UCLASS(Blueprintable)
class PLUPROCEDURALBUILDING_API AAGraphCoreElement : public AActor, public II_GraphAction
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAGraphCoreElement();
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostInitializeComponents() override;
	virtual void PostActorCreated() override;
	virtual void PostLoad() override;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SM;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	///массив узлов
	TArray<AActor*> TNodes;
	///массив мешей
	TArray<UStaticMeshComponent*>SMArray;
	///массив сплайнов
	TArray<USplineComponent*> SCArray;
	TArray<UProceduralMeshComponent*> PMCArray;
	///структура сборки данных
	TMap<FGuid,FArrayConnectionType> DataConnectNode;
	//Процедурные моменты
	//To make sure that the vertices also get copied for every PIE instance (No loss of actor data)
	UPROPERTY(NonPIEDuplicateTransient) 
	TArray<FVector> vertices;
	TArray<int32> Triangles;
	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> tangents;
	TArray<FLinearColor> vertexColors;
	//temp triangle arrays
	TArray<FVector> eachTriangleNormal;
	TArray<FProcMeshTangent> eachTriangleTangents;
	TArray<FLinearColor> eachTriangleVertexColors;
	//
	using Coord = double;
	using N = uint32_t;
	using Point = std::array<Coord, 2>;
	//
	std::vector<std::vector<Point>> polygon;
	std::vector<Point> polygonVertices;
	//
	void GetAllActorsLevel(TSubclassOf<UInterface> myInterfase,TArray<AActor*> &foundEnemies);
	void SearchNodesInTheWorld();
	void SearchBranches();
	void AddLineToBranch(FString NameComponent, FVector Start, FVector End, FVector RouteBranch);
	void AddStartEndDataToBranch(USplineComponent* Spline_, FVector Start, FVector End, FVector RouteBranch);
	void IGraphRebuildNodeSpace_Implementation() override;
	UFUNCTION(BlueprintCallable)
		void CRSp();
	UFUNCTION(BlueprintCallable)
        void CreateProceduralSections();
	void CreateSection();
	void AddVertexFloor();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
