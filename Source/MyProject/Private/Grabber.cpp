// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle =GetPhysicsHandle();
	if (PhysicsHandle==nullptr)
	{
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent()!=nullptr)
	{
		FVector TargetLocation= GetComponentLocation() + GetForwardVector()* HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation ,GetComponentRotation());
		DrawDebugSphere(GetWorld(),TargetLocation,10,10,FColor::Green,false,5);
	}
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle==nullptr)
	{
		return;
	}
	FHitResult HitResult;
	bool HasHit= GetGrabbableInReact(HitResult);
	
	if (HasHit)
	{
		UPrimitiveComponent* HitComponent= HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,10,10,FColor::Red,true,5);
		PhysicsHandle->GrabComponentAtLocationWithRotation(
		HitComponent,
		NAME_None,
		HitResult.ImpactNormal,
		GetComponentRotation()
		);
	}
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle= GetPhysicsHandle();
	if (PhysicsHandle==nullptr)
	{
		return;
	}
	if (PhysicsHandle->GetGrabbedComponent()!= nullptr)
	{
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result =GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result==nullptr)
	{
		UE_LOG(LogTemp,Error,TEXT("grabber request a UPhysicsHandleComponent"))
	}
	return Result;
}

bool UGrabber::GetGrabbableInReact(FHitResult& OutHitResult) const
{
	FVector Start=GetComponentLocation();
	FVector End=Start+(GetForwardVector()*MaxDistance);
	DrawDebugLine(GetWorld(),Start,End,FColor::Red);
	DrawDebugSphere(GetWorld(),End,10,10,FColor::Blue,true,5);

	FCollisionQueryParams Params= FCollisionQueryParams::DefaultQueryParam;
	FCollisionShape Sphere= FCollisionShape::MakeSphere(GrabRadius);
	FHitResult HitResult;
	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start,End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
		);
	
}

