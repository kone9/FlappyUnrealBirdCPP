// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_mode_custom.h"
#include <Kismet/GameplayStatics.h>
#include "Bird_pawn.h"
#include <Kismet/GameplayStatics.h>

AGame_mode_custom::AGame_mode_custom()
{

}


//Para llamar cuando se destruyen las columnas
void AGame_mode_custom::end_colums()
{
	if (GetWorld() == nullptr) return;

	cant_columns -= 1;

	if(cant_columns == 2)//sino hay más columns
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, TEXT("TENDRIA QUE INICAR ANIMACION CAMBIAR DE NIVEL"));
		nivel_winner = true;
		
		desactivar_actor();

		if (end_game_winner_sound == nullptr) return;
		UGameplayStatics::PlaySound2D(GetWorld(), end_game_winner_sound);
		
	}
	if (cant_columns == 1)//sino hay más columns
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, TEXT("TENDRIA QUE INICAR ANIMACION CAMBIAR DE NIVEL"));
		
		UGameplayStatics::OpenLevel(GetWorld(), new_level_name);

	}





}


//Desactiva las fisicas del actor principal para iniciar animación ganaste nivel
void AGame_mode_custom::desactivar_actor()
{
	TArray<AActor*> actor_with_tag{};
	FName tag_actor = TEXT("actor_tag");// add tag actor here
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), tag_actor, actor_with_tag);
	AActor* bird = nullptr;
	if (actor_with_tag.Num() > 0)//only if there are elements inside the array I look for it by index
	{
		bird = actor_with_tag[0];
	}

	if (bird == nullptr) return;
	if (Cast<ABird_pawn>(bird)->mesh_Bird == nullptr) return;
	Cast<ABird_pawn>(bird)->mesh_Bird->SetSimulatePhysics(false);//dejo de simular fisicas.


}
