// Fill out your copyright notice in the Description page of Project Settings.


#include "AGraphCoreElement.h"


// Sets default values
AAGraphCoreElement::AAGraphCoreElement()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AAGraphCoreElement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAGraphCoreElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AAGraphCoreElement::OnConstruction(const FTransform& Transform)
{
	//CRSp();
}
void AAGraphCoreElement::CRSp()
{
	TNodes.Empty();
	TNodes.Reset(100);
	SearchNodesInTheWorld();
	SearchBranches();
	II_GraphAction::Execute_IGraphRebuildNodeSpace(this);
}
void AAGraphCoreElement::GetAllActorsLevel(TSubclassOf<UInterface> myInterfase, TArray<AActor*> &foundEnemies)
{
	GLog->Log("GetAllActorsLevel");
	//TSubclassOf<AActor> classToFind;
	//classToFind = AA_Graph_Node_Base::StaticClass();
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, foundEnemies);
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), myInterfase, foundEnemies);
	UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), foundEnemies.Num());
}
void AAGraphCoreElement::SearchNodesInTheWorld()
{
	GetAllActorsLevel(UI_NodeGraph::StaticClass(),TNodes);
}
void AAGraphCoreElement::SearchBranches()
{
	for(int i = 0; i < TNodes.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("The integer value TNodes.Num: %d"), i);
		TArray<FConnectionType> connections_ = II_GraphAction::Execute_IGetConnectionNode(TNodes[i]);
		if (connections_.Num() > 0)
		{
			for(int j = 0; j < connections_.Num(); j++)
			{
				if (connections_[j].bOrientationConnectNode)
				{
					UE_LOG(LogTemp, Warning, TEXT("The integer value TNodes.connections_: %d"), j);
					II_GraphAction::Execute_IAddNode(connections_[j].aConnectionNode,TNodes[i],false,connections_[j].wightBranch);
					connections_[j].bConnectionSearch = true;
				}
			}
			//нужны данные в ноды, которые входят в узел и там не было предварительного расчета
			II_GraphAction::Execute_ISetConnectionNode(TNodes[i], connections_);
		}
		//если нет коннектов
		if (connections_.Num()==0)
		{
			//удалить ноду
		}
	}
	for(int i = 0; i < TNodes.Num(); i++)
	{
		II_GraphAction::Execute_ICreateExternalGuideLines(TNodes[i]);
	}
}
void AAGraphCoreElement::IGraphRebuildNodeSpace_Implementation()
{
	for (int i = 0; i < TNodes.Num(); i++)
		II_GraphAction::Execute_IGraphRebuildNodeSpace(TNodes[i]);
}
