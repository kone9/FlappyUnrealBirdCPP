// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Game_mode_custom.generated.h"

/**
 * 
 */

UCLASS()
class FLAPPYUNREALBIRDCPP_API AGame_mode_custom : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGame_mode_custom();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float velocity{ 10 };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool game_over = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool init_columns = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int actual_score{0};

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool nivel_winner{ false };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int nivel_max_score_winner{ 30 };


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int cant_columns{ 4 };

public:
	void end_colums();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> boss_colums;

public:
	UFUNCTION(BlueprintCallable)
	void desactivar_actor();


public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USoundBase* end_game_winner_sound;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName new_level_name = TEXT("new_level_name");// Level_Game

};
