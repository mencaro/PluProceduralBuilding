// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Graph_Node_Base.h"


#include "Components/SplineComponent.h"
#include "PluProceduralBuilding/Interfases/I_Branch.h"


// Sets default values
AA_Graph_Node_Base::AA_Graph_Node_Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
FGuid AA_Graph_Node_Base::IGetGUID_Implementation()
{
	if(!NodeGUID.IsValid())
	{
		NodeGUID = FGuid();
		NodeGUID = NodeGUID.NewGuid();
	}
	return NodeGUID;
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
}
void AA_Graph_Node_Base::IAddBranch_Implementation(AActor* br)
{
	ConnectionBranch.Add(br);
}
FArrayConnectionType AA_Graph_Node_Base::IGetConnectionNode_Implementation()
{
	ConnectionNodes.ThisMainPosition = this->GetActorLocation();
	ConnectionNodes.ThisMainPositionW = this->GetActorLocation();
	ConnectionNodes.ThisMainPositionW.Z = ConnectionNodes.ThisMainPositionW.Z + HeightRange;
	ConnectionNodes.pointOnThis = this;
	ConnectionNodes.RangeOuts = RangeNodeSpace;
	return ConnectionNodes;
}
void AA_Graph_Node_Base::ISetConnectionNode_Implementation(TArray<FConnectionType>& ct)
{
	//ConnectionNodes_.Empty();
	//ConnectionNodes_ = ct;
}

int AA_Graph_Node_Base::IGetRangeOuts_Implementation()
{
	return RangeNodeSpace;
}
int AA_Graph_Node_Base::IGetHeightNode_Implementation()
{
	return HeightRange;
}
FVector AA_Graph_Node_Base::IGetNodePositionInTheWorld_Implementation()
{
	return this->GetActorLocation();
}
void AA_Graph_Node_Base::IGraphRebuildNodeSpace_Implementation()
{
	// if (ConnectionNodes.Num() > 0)
	// {
	// 	for(int i = 0; i < ConnectionNodes.Num(); i++)
	// 	{
	// 		//if(ConnectionNodes[i].bConnectionSearch)
	// 		{
	// 			//if(!ConnectionNodes[i].bOrientationConnectNode)
	// 				//ConnectionNodes[i].route_relatively_node *= -1;
	// 			ConnectionNodes[i].angle_route = atan2(ConnectionNodes[i].route_relatively_node.X , ConnectionNodes[i].route_relatively_node.Y);
	// 			GLog->Log("IGraphRebuildNodeSpace_Implementation");
	// 		}
	// 		//else
	// 			//GLog->Log("ConnectionNodes[i].aConnectionBranch)==nullptr");
 //        }
	// 	SortFoAngle();
	// 	CreateSplineNode();
	// }
	// else if (ConnectionNodes.Num() == 1)
	// {
	// 	GLog->Log("ConnectionBranch.Num() == 1");
	// }
	// else if (ConnectionNodes.Num() == 0)
	// {
	// 	GLog->Log("ConnectionBranch.Num() == 0");
	// }
}

FConnectionType AA_Graph_Node_Base::ISearchBranchFromNodes_Implementation(AActor* node)
{
	// int re_i = -1;
	// for (int i = 0; i < ConnectionNodes.Num(); i++)
	// {
	// 	if(ConnectionNodes[i].aConnectionNode == node)
	// 	{
	// 		re_i = i;
	// 		break;
	// 	}
	// }
	// if (re_i != -1)
	// return  ConnectionNodes[re_i];
	// else if (re_i == -1)
	// 	return  FConnectionType();
	// else
		return  FConnectionType();
}

void AA_Graph_Node_Base::SortFoAngle()
{
	// for(int i = 0; i < ConnectionNodes.Num(); i++)
	// {
	// 	FConnectionType ct = ConnectionNodes[i];
	// 	for(int j = i+1; j < ConnectionNodes.Num(); j++)
	// 	{
	// 		if(ct.angle_route > ConnectionNodes[j].angle_route)
	// 		{
	// 			FConnectionType ct1 = ConnectionNodes[j];
	// 			ConnectionNodes[j] = ct;
	// 			ConnectionNodes[i] = ct1;
	// 			ct = ct1;
	// 		}
	// 	}
	// }
	// for(int i = 0; i < ConnectionNodes.Num(); i++)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("The VECTOR value is: %s"), *ConnectionNodes[i].route_relatively_node.ToString());
	// 	UE_LOG(LogTemp, Warning, TEXT("The РАДИАНЫ value is: %f"), ConnectionNodes[i].angle_route);
	// 	UE_LOG(LogTemp, Warning, TEXT("The ГРАДУСЫ value is: %f"), 90-ConnectionNodes[i].angle_route*(180/3.14));
	// }
}

void AA_Graph_Node_Base::CreateSplineNode()
{
	// FVector Point1R_1;FVector Point2R_1;FVector Point1L_1;FVector Point2L_1;
	// FVector Point1R_2;FVector Point2R_2;FVector Point1L_2;FVector Point2L_2;
	// ausc.Empty();
	// for(int i = 0; i < ConnectionNodes.Num(); i++)
	// {
	// 	USplineComponent *Spline_ = NewObject<USplineComponent>(this, USplineComponent::StaticClass());
	// 	Spline_->RegisterComponentWithWorld(GetWorld());
	// 	//center
	// 	Spline_->SetLocationAtSplinePoint(0,this->GetActorLocation(),ESplineCoordinateSpace::Type::World);
	// 	Spline_->SetTangentAtSplinePoint(0,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
	// 	Spline_->SetLocationAtSplinePoint(1,this->GetActorLocation()+ConnectionNodes[i].route_relatively_node*rangeOuts,ESplineCoordinateSpace::Type::World);
	// 	Spline_->SetTangentAtSplinePoint(1,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
	// 	ausc.Add(Spline_);
	// 	USplineComponent *Spline_R1 = NewObject<USplineComponent>(this, USplineComponent::StaticClass());
	// 	Spline_R1->RegisterComponentWithWorld(GetWorld());
	// 	USplineComponent *Spline_L1 = NewObject<USplineComponent>(this, USplineComponent::StaticClass());
	// 	Spline_L1->RegisterComponentWithWorld(GetWorld());
	// 	USplineComponent *Spline_RL1 = NewObject<USplineComponent>(this, USplineComponent::StaticClass());
	// 	Spline_RL1->RegisterComponentWithWorld(GetWorld());
	//
	// 	ausc.Add(Spline_R1);
	// 	ausc.Add(Spline_L1);
	// 	ausc.Add(Spline_RL1);
	// 	//right
	// 	Point1R_1 = ConnectionNodes[i].Point1R; Point2R_1 = ConnectionNodes[i].Point2R;
	// 	Point1L_1 = ConnectionNodes[i].Point1L; Point2L_1 = ConnectionNodes[i].Point2L;
	// 	{
	// 		Spline_R1->SetLocationAtSplinePoint(0,this->GetActorLocation(),ESplineCoordinateSpace::Type::World);
	// 		Spline_R1->SetTangentAtSplinePoint(0,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
	// 		Spline_R1->SetLocationAtSplinePoint(1,Point1R_1,ESplineCoordinateSpace::Type::World);
	// 		Spline_R1->SetTangentAtSplinePoint(1,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
	// 	}
	// 	{
	// 		Spline_L1->SetLocationAtSplinePoint(0,this->GetActorLocation(),ESplineCoordinateSpace::Type::World);
	// 		Spline_L1->SetTangentAtSplinePoint(0,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
	// 		Spline_L1->SetLocationAtSplinePoint(1,Point1L_1,ESplineCoordinateSpace::Type::World);
	// 		Spline_L1->SetTangentAtSplinePoint(1,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
	// 	}
	// 	
	// 	int k = i + 1;
	// 	if(i == ConnectionNodes.Num()-1) {k = 0;}
	// 	
	// 	Point1R_1 = ConnectionNodes[i].Point1R; Point2R_1 = ConnectionNodes[i].Point2R;
	// 	Point1L_1 = ConnectionNodes[i].Point1L; Point2L_1 = ConnectionNodes[i].Point2L;
	// 	Point1R_2 = ConnectionNodes[k].Point1R; Point2R_2 = ConnectionNodes[k].Point2R;
	// 	Point1L_2 = ConnectionNodes[k].Point1L; Point2L_2 = ConnectionNodes[k].Point2L;
	//
	// 	Spline_RL1->SetLocationAtSplinePoint(0,Point1R_1,ESplineCoordinateSpace::Type::World);
	// 	Spline_RL1->SetTangentAtSplinePoint(0,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
	// 	Spline_RL1->SetLocationAtSplinePoint(1,Point1L_2,ESplineCoordinateSpace::Type::World);
	// 	Spline_RL1->SetTangentAtSplinePoint(1,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
	// }
}

void AA_Graph_Node_Base::ICreateExternalGuideLines_Implementation()
{
	CreateExternalGuideLines();
}

void AA_Graph_Node_Base::CreateExternalGuideLines()
{
	// Splines_.Empty();
	// int j = 0;
	// for (int i = 0; i < ConnectionNodes_.Num(); i++)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("The CreateExternalGuideLines value TNodes.Num: %d"), i);
	// 	if((ConnectionNodes_[i].aConnectionNode != nullptr))
	// 	{
	// 		GLog->Log("StartCreateSplineAndPoint");
	// 		ConnectionNodes_[i].route_relatively_node = UBFL_MathGraph::FindRouteVectorBranch(this->GetActorLocation(),ConnectionNodes_[i].aConnectionNode->GetActorLocation());
	// 		ConnectionNodes_[i].route_relatively_node.Normalize();
	// 		FVector routeBranchNorm = ConnectionNodes_[i].route_relatively_node.CrossProduct(ConnectionNodes_[i].route_relatively_node, FVector(0,0,1));
	// 		GLog->Log(ConnectionNodes_[i].route_relatively_node.ToString());
	// 		//
	// 		FVector n1;FVector n2;
	// 		FVector point1_rigth; FVector point2_rigth;
	// 		FVector point1_left; FVector point2_left;
	// 		{
	// 			n1 = this->GetActorLocation() + ConnectionNodes_[i].route_relatively_node * II_NodeGraph::Execute_IGetRangeOuts(this);
	// 			n2 = ConnectionNodes_[i].aConnectionNode->GetActorLocation() + (ConnectionNodes_[i].route_relatively_node * (-1)) * II_NodeGraph::Execute_IGetRangeOuts(ConnectionNodes_[i].aConnectionNode);
	// 		}
	// 		
	// 		point1_rigth = n1 + routeBranchNorm * ConnectionNodes_[i].wightBranch;
	// 		point2_rigth = n2 + routeBranchNorm * ConnectionNodes_[i].wightBranch;
	//
	// 		point1_left = n1 + routeBranchNorm * (-1) * ConnectionNodes_[i].wightBranch;
	// 		point2_left = n2 + routeBranchNorm * (-1) * ConnectionNodes_[i].wightBranch;
	//
	// 		ConnectionNodes_[i].Point1C = n1;
	// 		ConnectionNodes_[i].Point2C = n2;
	// 		ConnectionNodes_[i].Point1R = point1_rigth;
	// 		ConnectionNodes_[i].Point2R = point2_rigth;
	// 		ConnectionNodes_[i].Point1L = point1_left;
	// 		ConnectionNodes_[i].Point2L = point2_left;
	//
	// 		FName name1 = *FString::Printf(TEXT("SplineMid %i"), i);
	// 		FName name2 = *FString::Printf(TEXT("SplineLeft %i"), i);
	// 		FName name3 = *FString::Printf(TEXT("SplineRigth %i"), i);
	// 		Splines_.Add(NewObject<USplineComponent>(this, USplineComponent::StaticClass()));
	// 		Splines_.Add(NewObject<USplineComponent>(this, USplineComponent::StaticClass()));
	// 		Splines_.Add(NewObject<USplineComponent>(this, USplineComponent::StaticClass()));
	// 		Splines_[j]->RegisterComponentWithWorld(GetWorld());
	// 		Splines_[j+1]->RegisterComponentWithWorld(GetWorld());
	// 		Splines_[j+2]->RegisterComponentWithWorld(GetWorld());
	//
	// 		AddStartEndDataToBranch(Splines_[j],n1,n2,ConnectionNodes_[i].route_relatively_node);
	// 		AddStartEndDataToBranch(Splines_[j+1],point1_left,point2_left,ConnectionNodes_[i].route_relatively_node);
	// 		AddStartEndDataToBranch(Splines_[j+2],point1_rigth,point2_rigth,ConnectionNodes_[i].route_relatively_node);
	// 		j+=3;
	// 	}
	// }
}
void AA_Graph_Node_Base::AddStartEndDataToBranch(USplineComponent* spline_, FVector n1, FVector n2, FVector routeBranch)
{
	GLog->Log("AddStartEndDataToBranch");
	spline_->SetLocationAtSplinePoint(0,n1,ESplineCoordinateSpace::Type::World);
	spline_->SetTangentAtSplinePoint(0,routeBranch,ESplineCoordinateSpace::Type::World);
	spline_->SetLocationAtSplinePoint(1,n2,ESplineCoordinateSpace::Type::World);
	spline_->SetTangentAtSplinePoint(1,routeBranch,ESplineCoordinateSpace::Type::World);
}
