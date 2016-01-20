// Fill out your copyright notice in the Description page of Project Settings.

#include "StarsAndPirates.h"
#include "EngineToolsLibrary.h"

void UEngineToolsLibrary::RemoveInvalid(TArray<AActor*> &TargetArray)
{
	TargetArray.RemoveAll([](AActor* a) { return (!a || a->IsPendingKill() || a->IsPendingKillPending()); });
}

int32 UEngineToolsLibrary::CountInvalid(TArray<AActor*> TargetArray)
{
	return TargetArray.FilterByPredicate([](AActor* a) { return (!a || a->IsPendingKill() || a->IsPendingKillPending()); }).Num();
}
