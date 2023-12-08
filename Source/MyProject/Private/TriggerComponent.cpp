// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

#include "Materials/MaterialExpressionWhileLoop.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick=true;
}

//BeginPlayEvent
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

//Tick Event
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AActor* Actor= AcceptableActor();
	if (Actor!=nullptr)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component!=nullptr)
		{
			Component->SetSimulatePhysics(false);
		}
			Actor->AttachToComponent(this,FAttachmentTransformRules::KeepWorldTransform,NAME_None);
			Mover->SetShouldMove(true);
		
	}
	else
	{
		Mover->SetShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover=NewMover;
}

AActor* UTriggerComponent::AcceptableActor()
{
	TArray<AActor*> Actors;
 	GetOverlappingActors(Actors);
 		for (AActor* Actor:Actors)
 		{
 			if (Actor->ActorHasTag(TagName))
 			{
 				return Actor;
 			}
 		}
	return nullptr;
}
