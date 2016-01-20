// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "EngineToolsLibrary.generated.h"

UCLASS()
class STARSANDPIRATES_API UEngineToolsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Utilities|Array")
		static void RemoveInvalid(UPARAM(ref) TArray<AActor*> &TargetArray);

	UFUNCTION(BlueprintCallable, Category = "Utilities|Array")
		static int32 CountInvalid(TArray<AActor*> TargetArray);
};
