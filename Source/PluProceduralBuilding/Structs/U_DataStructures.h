// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SplineComponent.h"
#include "UObject/Object.h"
#include "Components/SplineMeshComponent.h"
#include "U_DataStructures.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FConnectionType
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bOrientationConnectNode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int wightBranch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* aConnectionNode;
	//вектор направления ветки
	FVector route_relatively_node;
	//нормаль к ветке
	FVector routeBranchNorm;
	//
	//точки
	FVector PointStart; FVector PointEnd;
	//
	FVector PointStart_R; FVector PointEnd_R;
	FVector PointStart_L; FVector PointEnd_L;
	//крышка
	FVector PointStart_Rw; FVector PointEnd_Rw;
	FVector PointStart_Lw; FVector PointEnd_Lw;
	//угол поворота относительно узла
	double angle_route;
	//внешние линии
	
	FConnectionType()
	{
		bOrientationConnectNode = true;
		wightBranch = 40;
		angle_route = 0;
		
	}
	//
	// void AddConnectNode(AActor* act)
	// {
	// 	aConnectionNode = act;
	// }
	// double CalcAngle()
	// {
	// 	return atan(route_relatively_node.Y / route_relatively_node.X);
	// }
};
USTRUCT(BlueprintType)
struct FArrayConnectionType
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FConnectionType> ArrayData;
	FVector ThisMainPosition;
	AActor* pointOnThis;
	///значение расширения узла - удаления входа веток от центра
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RangeOuts;
	double angle0;
	FArrayConnectionType()
	{
		RangeOuts = 150;
		angle0 = -10000.0;
		pointOnThis = nullptr;
	}
};
USTRUCT(BlueprintType)
struct FBranchComponent
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseSpline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ESplineMeshAxis::Type> ForwardAxis;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> BranchMeshs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UClass*> BranchActs;
};
UENUM(BlueprintType)
enum class ESplineMeshType: uint8
{
	DEFAULT  UMETA(DisplayName = "Default Mesh"),
    START    UMETA(DisplayName = "Starting Mesh"),
    END      UMETA(DisplayName = "EndingMesh"),
};

USTRUCT(BlueprintType)
struct FBranchLineData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector n1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector n2;
};
UCLASS()
class PLUPROCEDURALBUILDING_API UU_DataStructures : public UObject
{
	GENERATED_BODY()
};
