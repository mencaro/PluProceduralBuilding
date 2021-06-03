// Fill out your copyright notice in the Description page of Project Settings.


#include "PluProceduralBuilding/ScriptLiblary/BFL_MathGraph.h"

FVector UBFL_MathGraph::FindRouteVectorBranch(FVector n1, FVector n2)
{
	return (n2 - n1);
}