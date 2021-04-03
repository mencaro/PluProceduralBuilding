// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include  "PluProceduralBuilding/Structs/U_DataStructures.h"
#include  "PluProceduralBuilding/Interfases/I_GraphAction.h"
#include  "PluProceduralBuilding/Interfases/I_Node.h"
#include "PluProceduralBuilding/ScriptLiblary/BFL_MathGraph.h"
#include "Misc/Guid.h"
#include "A_Graph_Node_Base.generated.h"

UCLASS()
class PLUPROCEDURALBUILDING_API AA_Graph_Node_Base : public AActor,public II_NodeGraph, public II_GraphAction
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AA_Graph_Node_Base();
	FGuid NodeGUID;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	///список соединений узла с остальными узлами графа
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		FArrayConnectionType ConnectionNodes;
	TArray<AActor*> ConnectionBranch;
	TArray<USplineComponent*> ausc;
	TArray<USplineComponent*>Splines_;
	///значение расширения узла - удаления входа веток от центра
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		int rangeOuts;
	///добавление узла связи в графе
	void IAddNode_Implementation(AActor* node, bool bTypeConnect, int wigth) override;
	void IAddBranch_Implementation(AActor* br) override;
	int IGetRangeOuts_Implementation() override;
	///получить список соединений узла с элементами графа
	FArrayConnectionType IGetConnectionNode_Implementation() override;
	void ISetConnectionNode_Implementation(TArray<FConnectionType>& ct) override;
	void IGraphRebuildNodeSpace_Implementation() override;
	FConnectionType ISearchBranchFromNodes_Implementation(AActor* node) override;
	void SortFoAngle();
	void CreateSplineNode();
	void ICreateExternalGuideLines_Implementation() override;
	void CreateExternalGuideLines();
	void AddStartEndDataToBranch(USplineComponent* spline_, FVector n1, FVector n2, FVector routeBranch);
	FGuid IGetGUID_Implementation() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
