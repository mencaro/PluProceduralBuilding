// Fill out your copyright notice in the Description page of Project Settings.


#include "PluProceduralBuilding/ScriptLiblary/BFL_MathGraph.h"

FVector UBFL_MathGraph::FindRouteVectorBranch(FVector n1, FVector n2)
{
	return (n2 - n1);
}

bool UBFL_MathGraph::FindFocusVecToVecByX(FVector n1)
{
	FVector n_vec;
	//________________________________________________________________________________________________________
	if (n_vec.DotProduct(n1,FVector(1.0,0.0,0.0)) > 0)
		return true;
	else
		return false;
	//________________________________________________________________________________________________________
}
bool UBFL_MathGraph::FindFocusVecToVecByY(FVector n1)
{
	FVector n_vec;
	//________________________________________________________________________________________________________
	if (n_vec.DotProduct(n1,FVector(0.0,1.0,0.0)) > 0)
		return true;
	else
		return false;
}

