// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

/**
 * 
 */

class ARENASHOOTER_API MyUtils
{
public:
	MyUtils();
	~MyUtils();
	static UBlueprint* GetBlueprintClass(FString Path);

};
