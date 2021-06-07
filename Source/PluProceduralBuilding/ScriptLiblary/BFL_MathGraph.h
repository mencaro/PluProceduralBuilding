// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BFL_MathGraph.generated.h"

/**
 * 
 */
UCLASS()
class PLUPROCEDURALBUILDING_API UBFL_MathGraph : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	public:
	static FVector FindRouteVectorBranch(FVector n1, FVector n2);
	static bool FindFocusVecToVecByX(FVector n1);
	static bool FindFocusVecToVecByY(FVector n1);
	static float FindAngleByVector(FVector n1, FVector n2);
};
