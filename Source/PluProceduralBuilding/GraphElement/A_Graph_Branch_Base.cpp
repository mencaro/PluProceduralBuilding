// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Graph_Branch_Base.h"

#include "Components/SplineMeshComponent.h"

void AA_Graph_Branch_Base::OnConstruction(const FTransform& Transform)
{  
	Super::OnConstruction(Transform);
}
// Sets default values
AA_Graph_Branch_Base::AA_Graph_Branch_Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	splineMid = CreateDefaultSubobject<USplineComponent>("SplineMid");
	splineLeftSide = CreateDefaultSubobject<USplineComponent>("SplineLeftSide");
	splineRightSide = CreateDefaultSubobject<USplineComponent>("SplineRightSide");
}

// Called when the game starts or when spawned
void AA_Graph_Branch_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AA_Graph_Branch_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AA_Graph_Branch_Base::IAddNode_Implementation(AActor* node, bool bTypeConnect, int wigth)
{
	if(bTypeConnect)
	{
		Node1 = node;
	}
	else
	{
		Node2 = node;
		II_GraphAction::Execute_IAddNode(Node2,Node1,false,wigth);
	}
	SetWightBranch(wigth,bTypeConnect);
}
void AA_Graph_Branch_Base::SetWightBranch(int w, bool bstart)
{
	if (bstart)
		wigthBranch_n1 = w;
	else
		wigthBranch_n2 = w;
}
void AA_Graph_Branch_Base::IGraphRebuildSplinePoint_Implementation()
{
	CreateSplineAndPoint();
}

void AA_Graph_Branch_Base::CreateSplineAndPoint()
{
	if((Node1 != nullptr) && (Node2 != nullptr))
	{
		GLog->Log("StartCreateSplineAndPoint");
		routeBranch = UBFL_MathGraph::FindRouteVectorBranch(Node1->GetActorLocation(),Node2->GetActorLocation());
		routeBranch.Normalize();
		FVector routeBranchNorm = routeBranch.CrossProduct(routeBranch, FVector(0,0,1));
		GLog->Log(routeBranch.ToString());
		//
		FVector n1 = Node1->GetActorLocation() + routeBranch * II_NodeGraph::Execute_IGetRangeOuts(Node1);
		FVector n2 = Node2->GetActorLocation() + (routeBranch * (-1)) * II_NodeGraph::Execute_IGetRangeOuts(Node2);
		AddStartEndDataToBranch(splineMid,n1,n2);
		//
		point1_rigth = n1 + routeBranchNorm * wigthBranch_n1;
		point2_rigth = n2 + routeBranchNorm * wigthBranch_n1;
		AddStartEndDataToBranch(splineRightSide,point1_rigth,point2_rigth);
		//
		point1_left = n1 + routeBranchNorm * (-1) * wigthBranch_n2;
		point2_left = n2 + routeBranchNorm * (-1) * wigthBranch_n2;
		AddStartEndDataToBranch(splineLeftSide,point1_left,point2_left);
	}
}

void AA_Graph_Branch_Base::AddStartEndDataToBranch(USplineComponent* spline_, FVector n1, FVector n2)
{
	spline_->SetLocationAtSplinePoint(0,n1,ESplineCoordinateSpace::Type::World);
	spline_->SetTangentAtSplinePoint(0,routeBranch,ESplineCoordinateSpace::Type::World);
	spline_->SetLocationAtSplinePoint(1,n2,ESplineCoordinateSpace::Type::World);
	spline_->SetTangentAtSplinePoint(1,routeBranch,ESplineCoordinateSpace::Type::World);
}
void AA_Graph_Branch_Base::CreateSplineMeshComponentForBranch(USplineComponent* spline_,TArray<FBranchComponent> BranchComponents_)
{
	const int32 SplinePoints = spline_->GetNumberOfSplinePoints();
	const int32 SplineLengths = spline_->GetSplineLength();
	for (int SplineCount = 0; SplineCount < (SplinePoints-1); SplineCount++)
	{
		for (int j = 0; j < BranchComponents_.Num(); j++)
		{
			USplineMeshComponent *SplineMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
			if(BranchComponents_[j].BranchMeshs.Num()>0)
			{
				UStaticMesh* StaticMesh = BranchComponents_[j].BranchMeshs[0];
				UMaterialInterface* Material = nullptr;
				ESplineMeshAxis::Type ForwardAxis = BranchComponents_[j].ForwardAxis;
				// update mesh details
				SplineMesh->SetStaticMesh(StaticMesh);
				SplineMesh->SetForwardAxis(ForwardAxis, true);
				SplineMesh->SetMaterial(0, Material);
				// initialize the object
				SplineMesh->RegisterComponentWithWorld(GetWorld());
				SplineMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
				SplineMesh->SetMobility(EComponentMobility::Movable);
				SplineMesh->AttachToComponent(spline_, FAttachmentTransformRules::KeepRelativeTransform);
				// define the positions of the points and tangents
				const FVector StartPoint = spline_->GetLocationAtSplinePoint(SplineCount, ESplineCoordinateSpace::Type::Local);
				const FVector StartTangent = spline_->GetTangentAtSplinePoint(SplineCount, ESplineCoordinateSpace::Type::Local);
				const FVector EndPoint = spline_->GetLocationAtSplinePoint(SplineCount + 1, ESplineCoordinateSpace::Type::Local);
				const FVector EndTangent = spline_->GetTangentAtSplinePoint(SplineCount + 1, ESplineCoordinateSpace::Type::Local);
				SplineMesh->SetStartAndEnd(StartPoint, StartTangent, EndPoint, EndTangent, true);
				// query physics
				SplineMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
			}
		}
	}
}

void AA_Graph_Branch_Base::BuildMeshSequence(USplineComponent* spline_,TArray<FBranchComponent> BranchComponents_)
{
	
}
FVector AA_Graph_Branch_Base::IGetRouteVectorBranch_Implementation()
{
	return routeBranch;
}
void AA_Graph_Branch_Base::IGetCalcPointBranch_Implementation(FVector& Point1R,FVector& Point2R,FVector& Point1L,FVector& Point2L)
{
	Point1R = point1_rigth;
	Point2R = point2_rigth;
	Point1L = point1_left;
	Point2L = point2_left;
}