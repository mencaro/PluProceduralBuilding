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
	//метка была ли векка найдена и просчитано направление
	bool bConnectionSearch;
	//вектор направления ветки
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector route_relatively_node;
	//точки
	FVector Point1C; FVector Point2C;
	FVector Point1R; FVector Point2R;
	FVector Point1L; FVector Point2L;
	//угол поворота относительно узла
	double angle_route;
	//внешние линии
	USplineComponent *SplineMid;
	USplineComponent *SplineRigth;
	USplineComponent *SplineLeft;
	FConnectionType()
	{
		bOrientationConnectNode = true;
		wightBranch = 20;
		bConnectionSearch = false;
		angle_route = 0;
		SplineMid = nullptr;
		SplineLeft = nullptr;
		SplineRigth = nullptr;
	}
	//
	void AddConnectNode(AActor* act)
	{
		aConnectionNode = act;
	}
	double CalcAngle()
	{
		return atan(route_relatively_node.Y / route_relatively_node.X);
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
