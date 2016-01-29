// Fill out your copyright notice in the Description page of Project Settings.

#include "StarsAndPirates.h"
#include "ArmComponent.h"


// Sets default values for this component's properties
UArmComponent::UArmComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostPhysics;
	bTickInEditor = true;
}

void UArmComponent::OnRegister()
{
	Super::OnRegister();

	UpdateDesiredArmLocation(false, false, 0.f);
}

void UArmComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateDesiredArmLocation(EnablePositionLag, EnableRotationLag, DeltaTime);
}

void UArmComponent::UpdateDesiredArmLocation(bool useLocationLag, bool useRotationLag, float DeltaTime)
{
	FRotator desiredRot = GetComponentRotation();

	// If inheriting rotation, check options for which components to inherit
	if (!bAbsoluteRotation)
	{
		if (!InheritPitch)
		{
			desiredRot.Pitch = RelativeRotation.Pitch;
		}

		if (!InheritYaw)
		{
			desiredRot.Yaw = RelativeRotation.Yaw;
		}

		if (!InheritRoll)
		{
			desiredRot.Roll = RelativeRotation.Roll;
		}
	}

	// Apply 'lag' to rotation if desired
	if (useRotationLag)
	{
		desiredRot = FMath::RInterpTo(PreviousDesiredRot, desiredRot, DeltaTime, RotationLagSpeed);
	}
	PreviousDesiredRot = desiredRot;

	FVector desiredLoc = GetComponentLocation();
	if (useLocationLag)
	{
		desiredLoc = FMath::VInterpTo(PreviousDesiredLoc, desiredLoc, DeltaTime, PositionLagSpeed);
	}
	PreviousDesiredLoc = desiredLoc;

	// Now offset camera position back along our rotation
	desiredLoc -= desiredRot.Vector() * TargetArmLength;

	// Form a transform for new world transform for camera
	FTransform wTransform(desiredRot, desiredLoc);
	// Convert to relative to component
	FTransform rTransform = wTransform.GetRelativeTransform(ComponentToWorld);

	//// Update socket location/rotation
	//RelativeSocketLocation = rTransform.GetLocation();
	//RelativeSocketRotation = rTransform.GetRotation();

	//UpdateChildTransforms();

	for (USceneComponent* child : AttachChildren)
	{
		child->SetRelativeTransform(rTransform);
	}
}

