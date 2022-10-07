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
	int score{0};

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool player_winner{ false };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int max_score{ 30 };


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int cant_columns{ 4 };

};
