// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Game_Widget.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYUNREALBIRDCPP_API UGame_Widget : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* score_text{ nullptr };


};
