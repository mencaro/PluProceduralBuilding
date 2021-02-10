﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_Branch.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, MinimalAPI)
class UI_Branch : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLUPROCEDURALBUILDING_API II_Branch
{
	GENERATED_BODY()
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "My_interfaces|GraphSystem")
        void IRebuildSplinePoint();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "My_interfaces|GraphSystem")
        FVector IGetRoute();
};