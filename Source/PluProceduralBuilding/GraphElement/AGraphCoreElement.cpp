// Fill out your copyright notice in the Description page of Project Settings.


#include "AGraphCoreElement.h"

#include <string>


// Sets default values
AAGraphCoreElement::AAGraphCoreElement()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(SM);
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
	Super::OnConstruction(Transform);
	CRSp();
}
void AAGraphCoreElement::CRSp()
{
	//The base name for all our components
	FName InitialName = FName("MyCompName");
	for (auto It = SMArray.CreateIterator(); It; It++)
	{
		(*It)->DestroyComponent();
	}
	SMArray.Empty();
	for (auto It = SCArray.CreateIterator(); It; It++)
	{
		(*It)->DestroyComponent();
	}
	SCArray.Empty();
	TNodes.Empty();
	//Register all the components
	RegisterAllComponents();
	for (int32 i = 0; i < 20; i++)
	{
		//Change the name for the next possible item
		FString Str = "MyCompName" + FString::FromInt(i+1);
		//Convert the FString to FName
		InitialName = (*Str);
		UStaticMeshComponent* NewComp = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(),InitialName);
		NewComp->RegisterComponent();
		NewComp->SetStaticMesh(SM->GetStaticMesh());
		//Set a random location based on the values we enter through the editor
		FVector Location;
		//Set the random seed in case we need to change our random values
		FMath::SRandInit(5);
		Location.X += FMath::RandRange(-FMath::Abs(3), FMath::Abs(3));
		Location.Y += FMath::RandRange(-FMath::Abs(4), FMath::Abs(4));
		NewComp->SetWorldLocation(Location);
		//NewSpline->RegisterComponentWithWorld(GetWorld());
		NewComp->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
		SMArray.Add(NewComp);
	}
	//
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
	DataConnectNode.Empty();
	UE_LOG(LogTemp, Warning, TEXT("СОБИРАЕМ УЗЛЫ: %d"), 0);
	for(int i = 0; i < TNodes.Num(); i++)
	{
		FGuid g = II_GraphAction::Execute_IGetGUID(TNodes[i]);
		DataConnectNode.Add(g,II_GraphAction::Execute_IGetConnectionNode(TNodes[i]));
	}
	UE_LOG(LogTemp, Warning, TEXT("СОБИРАЕМ ОБРАТНЫЕ ВЕТВИ: %d"), 0);
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		UE_LOG(LogTemp, Warning, TEXT("DataConnectNode.CreateIterator(): %d"), 0);
		UE_LOG(LogTemp, Warning, TEXT("It.Value().ArrayData.Num(): %d"), It.Value().ArrayData.Num());
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("It.Value().ArrayData.Num().i: %d"), i);
				if(It.Value().ArrayData[i].bOrientationConnectNode)
				{
					FConnectionType c = It.Value().ArrayData[i];
					c.bOrientationConnectNode = false;
					c.aConnectionNode = It.Value().pointOnThis;
					if(DataConnectNode.Contains(II_GraphAction::Execute_IGetGUID(It.Value().ArrayData[i].aConnectionNode)))
						DataConnectNode[II_GraphAction::Execute_IGetGUID(It.Value().ArrayData[i].aConnectionNode)].ArrayData.Add(c);
					UE_LOG(LogTemp, Warning, TEXT("ОБРАТ: %d"), i);
				}
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("ОБСЧЕТ: %d"), 0);
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				if(It.Value().ArrayData[i].aConnectionNode != nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("ОБСЧЕТ=: %d"), i);
					It.Value().ArrayData[i].route_relatively_node =
						UBFL_MathGraph::FindRouteVectorBranch
						(
							It.Value().ThisMainPosition,
							It.Value().ArrayData[i].aConnectionNode->GetActorLocation()
						);
					It.Value().ArrayData[i].route_relatively_node.Normalize();
					It.Value().ArrayData[i].routeBranchNorm =
						It.Value().ArrayData[i].route_relatively_node.CrossProduct(It.Value().ArrayData[i].route_relatively_node, FVector(0,0,1));
					//
					{
						It.Value().ArrayData[i].PointStart =
							It.Value().ThisMainPosition +
								It.Value().ArrayData[i].route_relatively_node * It.Value().RangeOuts;
						//
						It.Value().ArrayData[i].PointEnd =
							 It.Value().ArrayData[i].aConnectionNode->GetActorLocation() +
								(It.Value().ArrayData[i].route_relatively_node * (-1)) * It.Value().RangeOuts;
						//
						It.Value().ArrayData[i].PointStart_R =
							It.Value().ArrayData[i].PointStart + It.Value().ArrayData[i].routeBranchNorm * It.Value().ArrayData[i].wightBranch;
						It.Value().ArrayData[i].PointEnd_R =
                            It.Value().ArrayData[i].PointEnd + It.Value().ArrayData[i].routeBranchNorm * It.Value().ArrayData[i].wightBranch;
						It.Value().ArrayData[i].PointStart_L =
                            It.Value().ArrayData[i].PointStart + It.Value().ArrayData[i].routeBranchNorm * (-1) * It.Value().ArrayData[i].wightBranch;
						It.Value().ArrayData[i].PointEnd_L =
                            It.Value().ArrayData[i].PointEnd + It.Value().ArrayData[i].routeBranchNorm * (-1) * It.Value().ArrayData[i].wightBranch;
					}
				}
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("ДЕЛАЕМ ЛИНИИ: %d"), 0);
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("ДЕЛАЕМ ЛИНИИ=: %d"), i);
				if(It.Value().ArrayData[i].bOrientationConnectNode)
				{
					AddLineToBranch
					(
						"SC_Center_" + It.Key().ToString() + FString::FromInt(i+1),
						It.Value().ArrayData[i].PointStart,
						It.Value().ArrayData[i].PointEnd,
						It.Value().ArrayData[i].route_relatively_node
					);
					AddLineToBranch
                    (
                        "SC_Right_" + It.Key().ToString() + FString::FromInt(i+1),
                        It.Value().ArrayData[i].PointStart_R,
                        It.Value().ArrayData[i].PointEnd_R,
                        It.Value().ArrayData[i].route_relatively_node
                    );
					AddLineToBranch
                    (
                        "SC_Left_" + It.Key().ToString() + FString::FromInt(i+1),
                        It.Value().ArrayData[i].PointStart_L,
                        It.Value().ArrayData[i].PointEnd_L,
                        It.Value().ArrayData[i].route_relatively_node
                    );
				}
			}
		}
	}
}
void AAGraphCoreElement::IGraphRebuildNodeSpace_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("ДЕЛАЕМ ЛИНИИ МЕЖДУ ЛИНИЯМИ: %d"), 0);
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("СЧИТАЕМ УГЛЫ=: %d"), i);
				{
					It.Value().ArrayData[i].angle_route = atan2(It.Value().ArrayData[i].route_relatively_node.X , It.Value().ArrayData[i].route_relatively_node.Y);
				}
			}
		}
	}
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				FConnectionType ct = It.Value().ArrayData[i];
				for(int j = i+1; j < It.Value().ArrayData.Num(); j++)
				{
					if(ct.angle_route > It.Value().ArrayData[j].angle_route)
					{
						FConnectionType ct1 = It.Value().ArrayData[j];
						It.Value().ArrayData[j] = ct;
						It.Value().ArrayData[i] = ct1;
						ct = ct1;
					}
				}
			}
		}
	}
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("The УГОЛ: %f"), It.Value().ArrayData[i].angle_route);
			}
		}
	}
	for (auto It = DataConnectNode.CreateIterator(); It; ++It)
	{
		if (It.Value().ArrayData.Num()>0)
		{
			for(int i = 0; i < It.Value().ArrayData.Num(); i++)
			{
				//center
				AddLineToBranch
                (
                    "SC_CenterNode_" + It.Key().ToString() + FString::FromInt(i+1),
                    It.Value().ThisMainPosition,
                    It.Value().ArrayData[i].PointStart,//It.Value().ThisMainPosition + It.Value().ArrayData[i].route_relatively_node * It.Value().RangeOuts,
                    It.Value().ArrayData[i].route_relatively_node
                );
				// //right
				AddLineToBranch
                (
                    "SC_CenterNodeRight_" + It.Key().ToString() + FString::FromInt(i+1),
                    It.Value().ThisMainPosition,
                    It.Value().ArrayData[i].PointStart_R,
                    It.Value().ArrayData[i].route_relatively_node
                );
				//left
				AddLineToBranch
                (
                    "SC_CenterNodeLeft_" + It.Key().ToString() + FString::FromInt(i+1),
                    It.Value().ThisMainPosition,
                    It.Value().ArrayData[i].PointStart_L,
                    It.Value().ArrayData[i].route_relatively_node
                );
				
				int k = i + 1;
				if(i == It.Value().ArrayData.Num()-1) {k = 0;}
    
				AddLineToBranch
                (
                    "SC_RightLeftNode_" + It.Key().ToString() + FString::FromInt(i+1),
                    It.Value().ArrayData[i].PointStart_R,
                    It.Value().ArrayData[k].PointStart_L,
                    It.Value().ArrayData[i].route_relatively_node
                );
			}
		}
	}
}

void AAGraphCoreElement::AddLineToBranch(FString NameComponent, FVector Start, FVector End, FVector RouteBranch)
{
	FName InitialName = (*NameComponent);
	USplineComponent* SC = NewObject<USplineComponent>(this, USplineComponent::StaticClass(), InitialName);
	SC->RegisterComponent();
	AddStartEndDataToBranch(SC,Start,End,RouteBranch);
	SCArray.Add(SC);
}
void AAGraphCoreElement::AddStartEndDataToBranch(USplineComponent* Spline_, FVector Start, FVector End, FVector RouteBranch)
{
	GLog->Log("AddStartEndDataToBranch");
	Spline_->SetLocationAtSplinePoint(0,Start,ESplineCoordinateSpace::Type::World);
	Spline_->SetTangentAtSplinePoint(0,RouteBranch,ESplineCoordinateSpace::Type::World);
	Spline_->SetLocationAtSplinePoint(1,End,ESplineCoordinateSpace::Type::World);
	Spline_->SetTangentAtSplinePoint(1,RouteBranch,ESplineCoordinateSpace::Type::World);
}
