// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorPlatform.h"

#include "Game_mode_custom.h"

#include <Kismet/GameplayStatics.h>

#include <Engine/World.h>

#include "Engine/Engine.h"

#include "TimerManager.h"



// Sets default values
AFloorPlatform::AFloorPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFloorPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetWorld() == nullptr) return;
	
	GetWorld()->GetTimerManager().SetTimer(timer_handle, this, &AFloorPlatform::OnTimerOut, timer_to_end, repeat_timer);
	///////////

	
	
}

// Called every frame
void AFloorPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (my_game_mode == nullptr) return;
	if (my_game_mode->game_over == true) return;
	
	/*global_velocity = my_game_mode->velocity;
	AddActorLocalOffset(FVector(0, (global_velocity * 1000) * -1 * DeltaTime, 0));*/
	
	
	//AddActorLocalOffset(FVector(0, velocity * -1 * DeltaTime, 0));

	//if (GetActorLocation().Y <= positionReload)
	//{
	//	SetActorLocation(FVector(0, new_location, offset_z));
	//}

}

void AFloorPlatform::OnTimerOut()
{
	//game_mode = UGameplayStatics::GetGameMode( GetWorld() );
	if (GetWorld()->GetAuthGameMode() == nullptr)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("No se encontro el GameMode"));
		return;
	}

	my_game_mode = Cast<AGame_mode_custom>(GetWorld()->GetAuthGameMode());
}

