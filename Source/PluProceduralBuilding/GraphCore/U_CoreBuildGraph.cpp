// Fill out your copyright notice in the Description page of Project Settings.

#include "U_CoreBuildGraph.h"

UWorld* UU_CoreBuildGraph::GetWorld() const
{
	if (GIsEditor && !GIsPlayInEditorWorld) return nullptr;
	else if (GetOuter()) return GetOuter()->GetWorld();
	else return nullptr;
}
TArray<AActor*> UU_CoreBuildGraph::SearchNodes()
{
	TArray<AActor*> foundEnemies;
	GetAllActorsLevel(foundEnemies);
	return foundEnemies;
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

void UU_CoreBuildGraph::SetAllData(TMap<int, FVector> DataNodes_, TArray<FIntPoint> DataBranches_)
{
	DataNodes = DataNodes_;
	DataBranches = DataBranches_;
}

void UU_CoreBuildGraph::SpawnNodes()
{
	DataNodesActors.Empty();
	FVector a;
	UE_LOG(LogTemp, Warning, TEXT("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA: %d"), 0);
	for (auto It = DataNodes.CreateIterator(); It; ++It)
	{
		a = It.Value();
		break;
	}
	//
	for (auto It = DataNodes.CreateIterator(); It; ++It)
	{
		//
		FVector b = (It.Value() - a) * 100;
		//
		UE_LOG(LogTemp, Warning, TEXT("_It_Key_: %d"), It.Key());
		DataNodesActors.Add(It.Key(),FSpawnActors(AA_Graph_Node_Base::StaticClass(),FTransform(FRotator(0.0,0.0,0.0),b, FVector(1,1,1))));
		//
	}
	for (int i = 0; i < DataBranches.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("_It_Key_: %d"), i);
		if (DataNodesActors.Contains(DataBranches[i].X) && DataNodesActors.Contains(DataBranches[i].Y))
			II_GraphAction::Execute_IAddConnectionNode(DataNodesActors[ DataBranches[i].X ], DataNodesActors[ DataBranches[i].Y ], true, 200);
	}
}

AActor* UU_CoreBuildGraph::FSpawnActors(UClass* class_obj, FTransform SpawnLocation)
{
	AActor* SpawnedActor1 = GetWorld()->SpawnActor(class_obj, &SpawnLocation);
	GLog->Log("Constructor::AddActor");
	return SpawnedActor1;
}