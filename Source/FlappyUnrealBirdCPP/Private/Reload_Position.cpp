// Fill out your copyright notice in the Description page of Project Settings.


#include "Reload_Position.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UReload_Position::UReload_Position()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UReload_Position::BeginPlay()
{
	Super::BeginPlay();

	// ...
	platform = GetOwner();
}


// Called every frame
void UReload_Position::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (platform == nullptr) return;

	
	/*if (platform->GetActorLocation().Y <= positionReload)
	{
		platform->SetActorLocation( FVector(platform->GetActorLocation().X, new_location, platform->GetActorLocation().Z) ) ;
	}*/

}

