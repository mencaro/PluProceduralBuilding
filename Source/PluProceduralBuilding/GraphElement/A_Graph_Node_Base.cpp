// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Graph_Node_Base.h"

#include "PluProceduralBuilding/Interfases/I_Branch.h"


// Sets default values
AA_Graph_Node_Base::AA_Graph_Node_Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AA_Graph_Node_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AA_Graph_Node_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AA_Graph_Node_Base::IAddNode_Implementation(AActor* node, bool bTypeConnect, int wigth)
{
	FConnectionType ct;
	ct.bOrientationConnectNode = bTypeConnect;
	ct.wightBranch = wigth;
	ct.AddConnectNode(node);
	ConnectionNodes.Add(ct);
	if(bTypeConnect)
		II_GraphAction::Execute_IAddNode(node, this, false, wigth);
}
void AA_Graph_Node_Base::IAddBranch_Implementation(AActor* br)
{
	ConnectionBranch.Add(br);
}
TArray<FConnectionType> AA_Graph_Node_Base::IGetConnectionNode_Implementation()
{
	return ConnectionNodes;
}

int AA_Graph_Node_Base::IGetRangeOuts_Implementation()
{
	return rangeOuts;
}

void AA_Graph_Node_Base::IGraphRebuildNodeSpace_Implementation()
{
	if (ConnectionBranch.Num() > 1)
	{
		for(int i = 0; i < ConnectionBranch.Num(); i++)
		{
			FVector croute_relatively_node = II_Branch::Execute_IGetRoute(ConnectionBranch[i]);
			double aangle_route = atan(croute_relatively_node.Y / croute_relatively_node.X);;
			UE_LOG(LogTemp, Warning, TEXT("The float value is: %f"), aangle_route);
			GLog->Log("IGraphRebuildNodeSpace_Implementation");
        }
	}
	else if (ConnectionBranch.Num() == 1)
	{
		GLog->Log("ConnectionBranch.Num() == 1");
	}
	else if (ConnectionBranch.Num() == 0)
	{
		GLog->Log("ConnectionBranch.Num() == 0");
	}
}

FConnectionType AA_Graph_Node_Base::ISearchBranchFromNodes_Implementation(AActor* node)
{
	int re_i = -1;
	for (int i = 0; i < ConnectionNodes.Num(); i++)
	{
		if(ConnectionNodes[i].aConnectionNode == node)
		{
			re_i = i;
			break;
		}
	}
	if (re_i != -1)
	return  ConnectionNodes[re_i];
	else if (re_i == -1)
		return  FConnectionType();
	else
		return  FConnectionType();
}