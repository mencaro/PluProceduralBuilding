﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include  "PluProceduralBuilding/Structs/U_DataStructures.h"
#include "I_GraphAction.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, MinimalAPI)
class UI_GraphAction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLUPROCEDURALBUILDING_API II_GraphAction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "My_interfaces|GraphSystem")
		FGuid IGetGUID();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "My_interfaces|GraphSystem")
        void IAddNode(AActor* node, bool bTypeConnect, int wigth);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "My_interfaces|GraphSystem")
		void IAddConnectionNode(AActor* node, bool bTypeConnect, int wigth);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "My_interfaces|GraphSystem")
        void IAddBranch(AActor* br);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "My_interfaces|GraphSystem")
        FArrayConnectionType IGetConnectionNode();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "My_interfaces|GraphSystem")
        void ISetConnectionNode(TArray<FConnectionType> &ct);
	///пересобрать весь граф
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "My_interfaces|GraphSystem")
        void IGraphRebuildCircuit();
	///перерасчитать точки сплайна у ветки
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "My_interfaces|GraphSystem")
        void ICreateExternalGuideLines();
	///пересобрать область пространства у узла графа
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "My_interfaces|GraphSystem")
        void IGraphRebuildNodeSpace();
	///найти связь между узлами графа
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "My_interfaces|GraphSystem")
        FConnectionType ISearchBranchFromNodes(AActor* node);
};
