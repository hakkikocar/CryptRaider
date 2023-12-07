// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick=true;
	UE_LOG(LogTemp,Warning,TEXT("constructer çalıştı"));
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
	UE_LOG(LogTemp,Display,TEXT("tick çalışıyor çalıştı"));


	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	if (Actors.Num()>0)
	{
		FString Name=Actors[0]->GetActorNameOrLabel();
		UE_LOG(LogTemp,Display,TEXT("arraydeki eleman %s"), );
	}
}
