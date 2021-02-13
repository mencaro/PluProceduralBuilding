// Fill out your copyright notice in the Description page of Project Settings.

#include "U_CoreBuildGraph.h"

UWorld* UU_CoreBuildGraph::GetWorld() const
{
	if (GIsEditor && !GIsPlayInEditorWorld) return nullptr;
	else if (GetOuter()) return GetOuter()->GetWorld();
	else return nullptr;
}
void UU_CoreBuildGraph::IGraphRebuildCircuit_Implementation()
{
	GLog->Log("GraphRebuildCircuit_Start");	
	TNodes.Empty();
	TBranches.Empty();
	TNodes.Reset(100);
	TBranches.Reset(100);
	TNodes = SearchNodes();
	SearchBranches();
	SearchReverseBranches();
	II_GraphAction::Execute_IGraphRebuildNodeSpace(this);
	//сформировать составляющие узла
	GLog->Log("GraphRebuildCircuit_End");
}
TArray<AActor*> UU_CoreBuildGraph::SearchNodes()
{
	TArray<AActor*> foundEnemies;
	GetAllActorsLevel(foundEnemies);
	return foundEnemies;
}

void UU_CoreBuildGraph::SearchBranches()
{
	for(int i = 0; i < TNodes.Num(); i++)
	{
		TArray<FConnectionType> connections_ = II_GraphAction::Execute_IGetConnectionNode(TNodes[i]);
		if (connections_.Num()>0)
		{
			for(int j = 0; j < connections_.Num(); j++)
			{
				if (connections_[j].bOrientationConnectNode)
				{
					AActor* SpawnedActor1 = GetWorld()->SpawnActor(AA_Graph_Branch_Base::StaticClass(), &TNodes[i]->GetActorTransform());
					II_GraphAction::Execute_IAddNode(SpawnedActor1, TNodes[i], true, connections_[j].wightBranch);
					II_GraphAction::Execute_IAddNode(SpawnedActor1, connections_[j].aConnectionNode, false, connections_[j].wightBranch);
					II_GraphAction::Execute_IGraphRebuildSplinePoint(SpawnedActor1);
					connections_[j].aConnectionBranch = SpawnedActor1;
					//настроить ветку, дать координары
					TBranches.Add(SpawnedActor1);
				}
			}
			II_GraphAction::Execute_ISetConnectionNode(TNodes[i], connections_);
		}
		//если нет коннектов
		if (connections_.Num()==0)
		{
			//удалить ноду
		}
	}
}

void UU_CoreBuildGraph::SearchReverseBranches()
{
	for(int i = 0; i < TNodes.Num(); i++)
	{
		TArray<FConnectionType> connections_ = II_GraphAction::Execute_IGetConnectionNode(TNodes[i]);
		if (connections_.Num()>0)
		{
			for(int j = 0; j < connections_.Num(); j++)
			{
				if (!connections_[j].bOrientationConnectNode)
				{
					FConnectionType searchReverseNode = II_GraphAction::Execute_ISearchBranchFromNodes(connections_[j].aConnectionNode,TNodes[i]);
					if (searchReverseNode.aConnectionNode != nullptr)
					{
						connections_[j].aConnectionBranch = searchReverseNode.aConnectionBranch;
					}
				}
			}
		}
		II_GraphAction::Execute_ISetConnectionNode(TNodes[i], connections_);
	}
}
void UU_CoreBuildGraph::IGraphRebuildNodeSpace_Implementation()
{
	for (int i = 0; i < TNodes.Num(); i++)
		II_GraphAction::Execute_IGraphRebuildNodeSpace(TNodes[i]);
}

void UU_CoreBuildGraph::GetAllActorsLevel(TArray<AActor*> &foundEnemies)
{
	TSubclassOf<AActor> classToFind;
	classToFind = AA_Graph_Node_Base::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, foundEnemies);
}

void UU_CoreBuildGraph::GetAllActorsLevelWithMyInterfase(TSubclassOf<UInterface> myInterfase, TArray<AActor*> &foundEnemies)
{
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), myInterfase, foundEnemies);
}