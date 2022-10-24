// Fill out your copyright notice in the Description page of Project Settings.


#include "Colums_reload_position.h"

#include "GameFramework/Actor.h"
#include "Engine/Engine.h"

#include "Game_mode_custom.h"

#include <Kismet/GameplayStatics.h>

#include <Engine/World.h>

#include "Engine/Engine.h"

#include "TimerManager.h"

#include "Kismet/KismetMathLibrary.h"

#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UColums_reload_position::UColums_reload_position()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UColums_reload_position::BeginPlay()
{
	Super::BeginPlay();

	// ...
	columns = GetOwner();

	GetWorld()->GetTimerManager().SetTimer(timer_handle_search_Game_mode, this, &UColums_reload_position::OnTimerOut_Search_Game_mode, 0.1, false);//search game mode
}


// Called every frame
void UColums_reload_position::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (columns == nullptr) return;
	if (ref_box_collision == nullptr) return;
	if (my_game_mode == nullptr) return;
	if (my_game_mode->game_over == true) return;

	if (columns->GetActorLocation().Y < positionReload)//si la posicion es menor a la posicion de reinicio
	{
		//if (my_game_mode->actual_score != my_game_mode->nivel_max_score_winner)//si el jugador no gano la partida en reposicionnar las sigo reposicionnando
		//{
		diferencia_posicion = columns->GetActorLocation().Y - positionReload;//cuando llega al final hay un desplazamiento para fixear

		//nueva posicion fixeada con la diferencia en la posición
		columns->SetActorLocation(FVector(
			columns->GetActorLocation().X,
			new_location + diferencia_posicion,//se suma la diferencia
			UKismetMathLibrary::RandomFloatInRange(minimum_z, maximum_z)
		));
		
		ref_box_collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//vuelvo a habilitar la colision
		/*}
		else
		{
			my_game_mode->end_colums();

			if (GetOwner() == nullptr) return;
			GetOwner()->Destroy();
		}*/


	}

}


//search game mode despues de 0.1 segundos sino puede haber un puntero colgado
void UColums_reload_position::OnTimerOut_Search_Game_mode()
{
	if (GetWorld()->GetAuthGameMode() == nullptr)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("No se encontro el GameMode"));
		return;
	}
	if (GetOwner() == nullptr) return;

	my_game_mode = Cast<AGame_mode_custom>(GetWorld()->GetAuthGameMode());
	ref_box_collision = Cast<UBoxComponent>( GetOwner()->GetComponentByClass(UBoxComponent::StaticClass()) ); //busco el box component
}

