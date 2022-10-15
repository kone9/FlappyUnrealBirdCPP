// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstance_FlappyUnrealBird.generated.h"

/**
 * 
 */


//Global UENUM enumeracion para determinar nivel actual
UENUM(BlueprintType)
enum class ActualNivel : uint8
{
	nivel_1 UMETA(DisplayName = "nivel_1"),
	nivel_2 UMETA(DisplayName = "nivel_2"),
	nivel_3 UMETA(DisplayName = "nivel_3"),
	nivel_4 UMETA(DisplayName = "nivel_4")
};



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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ActualNivel estoy_en_nivel{ ActualNivel::nivel_1 };


	

};
