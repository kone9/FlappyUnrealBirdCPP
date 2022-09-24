// Fill out your copyright notice in the Description page of Project Settings.


#include "Reload_Position.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"

#include "Game_mode_custom.h"

#include <Kismet/GameplayStatics.h>

#include <Engine/World.h>

#include "Engine/Engine.h"

#include "TimerManager.h"


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

	GetWorld()->GetTimerManager().SetTimer(timer_handle_search_Game_mode, this, &UReload_Position::OnTimerOut_Search_Game_mode, 0.1, false);//search game mode
}


// Called every frame
void UReload_Position::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (platform == nullptr) return;
	if (my_game_mode == nullptr) return;
	if (my_game_mode->game_over == true) return;

	if (platform->GetActorLocation().Y < positionReload)
	{
		diferencia_posicion = platform->GetActorLocation().Y - positionReload;//cuando llega al final hay un desplazamiento para fixear

		//nueva posicion fixeada con la diferencia en la posición
		platform->SetActorLocation(FVector(
			platform->GetActorLocation().X,
			new_location + diferencia_posicion,//se suma la diferencia
			platform->GetActorLocation().Z
		));

	}

	/*if (platform->GetActorLocation().Y <= positionReload)
	{
		platform->SetActorLocation( FVector(platform->GetActorLocation().X, new_location, platform->GetActorLocation().Z) ) ;
	}*/

}

void UReload_Position::OnTimerOut_Search_Game_mode()
{
	if (GetWorld()->GetAuthGameMode() == nullptr)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("No se encontro el GameMode"));
		return;
	}

	my_game_mode = Cast<AGame_mode_custom>(GetWorld()->GetAuthGameMode());
}

