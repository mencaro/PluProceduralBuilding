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
void AA_Graph_Node_Base::ISetConnectionNode_Implementation(TArray<FConnectionType>& ct)
{
	ConnectionNodes = ct;
}

int AA_Graph_Node_Base::IGetRangeOuts_Implementation()
{
	return rangeOuts;
}

void AA_Graph_Node_Base::IGraphRebuildNodeSpace_Implementation()
{
	if (ConnectionNodes.Num() > 1)
	{
		for(int i = 0; i < ConnectionNodes.Num(); i++)
		{
			if(ConnectionNodes[i].aConnectionBranch != nullptr)
			{
				ConnectionNodes[i].route_relatively_node = II_Branch::Execute_IGetRouteVectorBranch(ConnectionNodes[i].aConnectionBranch);
				if(!ConnectionNodes[i].bOrientationConnectNode)
					ConnectionNodes[i].route_relatively_node *= -1;
				ConnectionNodes[i].angle_route = atan(ConnectionNodes[i].route_relatively_node.X / ConnectionNodes[i].route_relatively_node.Y);
				ConnectionNodes[i].angle_route = atan2(ConnectionNodes[i].route_relatively_node.X , ConnectionNodes[i].route_relatively_node.Y);
				GLog->Log("IGraphRebuildNodeSpace_Implementation");
			}
			else
				GLog->Log("ConnectionNodes[i].aConnectionBranch)==nullptr");
        }
		SortFoAngle();
		CreateSplineNode();
	}
	else if (ConnectionNodes.Num() == 1)
	{
		GLog->Log("ConnectionBranch.Num() == 1");
	}
	else if (ConnectionNodes.Num() == 0)
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

void AA_Graph_Node_Base::SortFoAngle()
{
	for(int i = 0; i < ConnectionNodes.Num(); i++)
	{
		FConnectionType ct = ConnectionNodes[i];
		for(int j = i+1; j < ConnectionNodes.Num(); j++)
		{
			if(ct.angle_route > ConnectionNodes[j].angle_route)
			{
				FConnectionType ct1 = ConnectionNodes[j];
				ConnectionNodes[j] = ct;
				ConnectionNodes[i] = ct1;
				ct = ct1;
			}
		}
	}
	for(int i = 0; i < ConnectionNodes.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("The VECTOR value is: %s"), *ConnectionNodes[i].route_relatively_node.ToString());
		UE_LOG(LogTemp, Warning, TEXT("The РАДИАНЫ value is: %f"), ConnectionNodes[i].angle_route);
		UE_LOG(LogTemp, Warning, TEXT("The ГРАДУСЫ value is: %f"), 90-ConnectionNodes[i].angle_route*(180/3.14));
	}
}

void AA_Graph_Node_Base::CreateSplineNode()
{
	for(int i = 0; i < ConnectionNodes.Num(); i++)//ConnectionNodes.Num()
	{
		USplineComponent *Spline_ = NewObject<USplineComponent>(this, USplineComponent::StaticClass());
		Spline_->RegisterComponentWithWorld(GetWorld());
		USplineComponent *Spline_R1 = NewObject<USplineComponent>(this, USplineComponent::StaticClass());
		Spline_R1->RegisterComponentWithWorld(GetWorld());
		USplineComponent *Spline_L1 = NewObject<USplineComponent>(this, USplineComponent::StaticClass());
		Spline_L1->RegisterComponentWithWorld(GetWorld());
		USplineComponent *Spline_RL1 = NewObject<USplineComponent>(this, USplineComponent::StaticClass());
		Spline_RL1->RegisterComponentWithWorld(GetWorld());

		FVector Point1R_1;FVector Point2R_1;FVector Point1L_1;FVector Point2L_1;
		FVector Point1R_2;FVector Point2R_2;FVector Point1L_2;FVector Point2L_2;
		
		//center
		Spline_->SetLocationAtSplinePoint(0,this->GetActorLocation(),ESplineCoordinateSpace::Type::World);
		Spline_->SetTangentAtSplinePoint(0,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
		Spline_->SetLocationAtSplinePoint(1,this->GetActorLocation()+ConnectionNodes[i].route_relatively_node*rangeOuts,ESplineCoordinateSpace::Type::World);
		Spline_->SetTangentAtSplinePoint(1,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
		//right
		II_Branch::Execute_IGetCalcPointBranch(ConnectionNodes[i].aConnectionBranch, Point1R_1, Point2R_1, Point1L_1, Point2L_1);
		if(ConnectionNodes[i].bOrientationConnectNode)
		{
			Spline_R1->SetLocationAtSplinePoint(0,this->GetActorLocation(),ESplineCoordinateSpace::Type::World);
			Spline_R1->SetTangentAtSplinePoint(0,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
			Spline_R1->SetLocationAtSplinePoint(1,Point1R_1,ESplineCoordinateSpace::Type::World);
			Spline_R1->SetTangentAtSplinePoint(1,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
		}
		else
		{
			Spline_R1->SetLocationAtSplinePoint(0,this->GetActorLocation(),ESplineCoordinateSpace::Type::World);
			Spline_R1->SetTangentAtSplinePoint(0,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
			Spline_R1->SetLocationAtSplinePoint(1,Point2R_1,ESplineCoordinateSpace::Type::World);
			Spline_R1->SetTangentAtSplinePoint(1,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
		}
		//left
		II_Branch::Execute_IGetCalcPointBranch(ConnectionNodes[i].aConnectionBranch, Point1R_1, Point2R_1, Point1L_1, Point2L_1);
		if(ConnectionNodes[i].bOrientationConnectNode)
		{
			Spline_L1->SetLocationAtSplinePoint(0,this->GetActorLocation(),ESplineCoordinateSpace::Type::World);
			Spline_L1->SetTangentAtSplinePoint(0,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
			Spline_L1->SetLocationAtSplinePoint(1,Point1L_1,ESplineCoordinateSpace::Type::World);
			Spline_L1->SetTangentAtSplinePoint(1,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
		}
		else
		{
			Spline_L1->SetLocationAtSplinePoint(0,this->GetActorLocation(),ESplineCoordinateSpace::Type::World);
			Spline_L1->SetTangentAtSplinePoint(0,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
			Spline_L1->SetLocationAtSplinePoint(1,Point2L_1,ESplineCoordinateSpace::Type::World);
			Spline_L1->SetTangentAtSplinePoint(1,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
		}
		
		int k = i + 1;
		if(i == ConnectionNodes.Num()-1) {k = 0;}
		
		II_Branch::Execute_IGetCalcPointBranch(ConnectionNodes[i].aConnectionBranch, Point1R_1, Point2R_1, Point1L_1, Point2L_1);
		II_Branch::Execute_IGetCalcPointBranch(ConnectionNodes[k].aConnectionBranch, Point1R_2, Point2R_2, Point1L_2, Point2L_2);
		
		if((ConnectionNodes[i].bOrientationConnectNode)&&(!ConnectionNodes[k].bOrientationConnectNode))
		{
			Spline_RL1->SetLocationAtSplinePoint(0,Point1R_1,ESplineCoordinateSpace::Type::World);
			Spline_RL1->SetTangentAtSplinePoint(0,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
			Spline_RL1->SetLocationAtSplinePoint(1,Point2R_2,ESplineCoordinateSpace::Type::World);
			Spline_RL1->SetTangentAtSplinePoint(1,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
		}
		else if((!ConnectionNodes[i].bOrientationConnectNode)&&(ConnectionNodes[k].bOrientationConnectNode))
		{
			Spline_RL1->SetLocationAtSplinePoint(0,Point2L_1,ESplineCoordinateSpace::Type::World);
			Spline_RL1->SetTangentAtSplinePoint(0,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
			Spline_RL1->SetLocationAtSplinePoint(1,Point1L_2,ESplineCoordinateSpace::Type::World);
			Spline_RL1->SetTangentAtSplinePoint(1,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
		}
		else if((ConnectionNodes[i].bOrientationConnectNode)&&(ConnectionNodes[k].bOrientationConnectNode))
		{
			Spline_RL1->SetLocationAtSplinePoint(0,Point1R_1,ESplineCoordinateSpace::Type::World);
			Spline_RL1->SetTangentAtSplinePoint(0,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
			Spline_RL1->SetLocationAtSplinePoint(1,Point1L_2,ESplineCoordinateSpace::Type::World);
			Spline_RL1->SetTangentAtSplinePoint(1,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
		}
		else if((!ConnectionNodes[i].bOrientationConnectNode)&&(!ConnectionNodes[k].bOrientationConnectNode))
		{
			Spline_RL1->SetLocationAtSplinePoint(0,Point2L_1,ESplineCoordinateSpace::Type::World);
			Spline_RL1->SetTangentAtSplinePoint(0,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
			Spline_RL1->SetLocationAtSplinePoint(1,Point2R_2,ESplineCoordinateSpace::Type::World);
			Spline_RL1->SetTangentAtSplinePoint(1,ConnectionNodes[i].route_relatively_node,ESplineCoordinateSpace::Type::World);
		}
	}
}

