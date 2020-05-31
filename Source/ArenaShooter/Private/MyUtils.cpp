// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUtils.h"

MyUtils::MyUtils()
{
}

MyUtils::~MyUtils()
{

}

UBlueprint* MyUtils::GetBlueprintClass(FString Path)
{
	UObject* ObjectsToGet = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, (TEXT("%s"), *Path)));
	UBlueprint* DefaultBP = Cast<UBlueprint>(ObjectsToGet);
	if (!DefaultBP) { return nullptr; }
	UClass* DefaultClass = DefaultBP->StaticClass();
	if (!DefaultClass) { return nullptr; }
	return DefaultBP;
}
