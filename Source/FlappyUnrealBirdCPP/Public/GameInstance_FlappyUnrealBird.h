// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstance_FlappyUnrealBird.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYUNREALBIRDCPP_API UGameInstance_FlappyUnrealBird : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int max_score{ 15 };

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool start_game_once{ false };

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int score_actual{ 0 };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int cant_lifes{ 3 };

};
