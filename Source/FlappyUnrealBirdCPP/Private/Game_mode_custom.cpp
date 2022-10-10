// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_mode_custom.h"

AGame_mode_custom::AGame_mode_custom()
{

}


//Para llamar cuando se destruyen las columnas
void AGame_mode_custom::end_colums()
{
	cant_columns -= 1;

	if(cant_columns < 1)//sino hay más columns
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, TEXT("TENDRIA QUE INSTANCIAR LA COLUMNA BOSS"));
	}
}
