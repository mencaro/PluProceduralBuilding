// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "PluProceduralBuilding/Interfases/I_GraphAction.h"
#include  "PluProceduralBuilding/Interfases/I_Node.h"
#include "PluProceduralBuilding/Interfases/I_GraphAction.h"
#include "PluProceduralBuilding/Structs/U_DataStructures.h"
#include "PluProceduralBuilding/ScriptLiblary/BFL_MathGraph.h"
#include "Math/UnrealMath.h"
#include "PluProceduralBuilding/Interfases/I_Branch.h"

#include "A_Graph_Branch_Base.generated.h"

UCLASS()
class PLUPROCEDURALBUILDING_API AA_Graph_Branch_Base : public AActor, public II_GraphAction, public  II_Branch
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AA_Graph_Branch_Base();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FBranchComponent> BranchComponents;
protected:
	void OnConstruction(const FTransform& Transform);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	AActor* Node1;//nodeIn;
	AActor* Node2;//nodeOut;
	///направляющий вектор ветки графа
	FVector routeBranch;
	int wigthBranch_n1;
	int wigthBranch_n2;
	void IAddNode_Implementation(AActor* node, bool bTypeConnect, int wigth) override;
	void IGraphRebuildSplinePoint_Implementation() override;
	FVector IGetRoute_Implementation() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USplineComponent* splineMid;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USplineComponent* splineRightSide;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USplineComponent* splineLeftSide;

	void SetWightBranch(int w, bool bstart);
	void CreateSplineAndPoint();
	UFUNCTION(BlueprintCallable)
	void CreateSplineMeshComponentForBranch(USplineComponent* spline_,TArray<FBranchComponent> BranchComponents_);
	void BuildMeshSequence(USplineComponent* spline_,TArray<FBranchComponent> BranchComponents_);
	void AddStartEndDataToBranch(USplineComponent* spline_, FVector n1, FVector n2);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
