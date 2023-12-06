// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
}

//BeginPlayEvent
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Error,TEXT("başarıya oluştu ve begin play çalıştı"));
}

//Tick Event
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
