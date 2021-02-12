// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include  "PluProceduralBuilding/Structs/U_DataStructures.h"
#include "Kismet/GameplayStatics.h"
#include  "PluProceduralBuilding/Interfases/I_GraphAction.h"
#include  "PluProceduralBuilding/GraphElement/A_Graph_Node_Base.h"
#include "PluProceduralBuilding/GraphElement/A_Graph_Branch_Base.h"
#include "U_CoreBuildGraph.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PLUPROCEDURALBUILDING_API UU_CoreBuildGraph : public UObject, public II_GraphAction
{
	GENERATED_BODY()
	
	protected:
		virtual UWorld* GetWorld() const override;
		TArray<AActor*> TNodes;
		TArray<AActor*> TBranches;
	UFUNCTION(BlueprintCallable)
		void IGraphRebuildCircuit_Implementation() override;
		void IGraphRebuildNodeSpace_Implementation() override;
	private:
		TArray<AActor*> SearchNodes();
		void SearchBranches();
		void SearchReverseBranches();
		void GetAllActorsLevel(TArray<AActor*> &foundEnemies);
	UFUNCTION(BlueprintPure)
        void GetAllActorsLevelWithMyInterfase(TSubclassOf<UInterface> myInterfase, TArray<AActor*> &foundEnemies);
};
