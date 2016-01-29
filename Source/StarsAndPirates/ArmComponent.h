// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "ArmComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARSANDPIRATES_API UArmComponent : public USceneComponent
{
	GENERATED_BODY()

public:	

	UArmComponent();

	virtual void OnRegister() override;

	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
		float TargetArmLength = 100.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
		bool InheritYaw = true;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
		bool InheritPitch = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
		bool InheritRoll = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
		bool EnablePositionLag = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
		bool EnableRotationLag = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (editcondition = "EnablePositionLag", ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))
		float PositionLagSpeed = 10.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (editcondition = "EnableRotationLag", ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))
		float RotationLagSpeed = 10.f;

protected:

	virtual void UpdateDesiredArmLocation(bool useLocationLag, bool useRotationLag, float DeltaTime);

	/** Cached component-space socket location */
	FVector RelativeSocketLocation;
	/** Cached component-space socket rotation */
	FQuat RelativeSocketRotation;

private:

	FName SocketName;
	FRotator PreviousDesiredRot;
	FVector  PreviousDesiredLoc;
};
