// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	AActor* aConnectionBranch;
	//
	FConnectionType()
	{
		bOrientationConnectNode = true;
		wightBranch = 20;
		aConnectionNode = nullptr;
	}
	//
	void AddConnectNode(AActor* act)
	{
		aConnectionNode = act;
	}
	void AddConnectBranch(AActor* act)
	{
		aConnectionBranch = act;
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
