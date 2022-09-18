// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorPlatform.generated.h"

UCLASS()
class FLAPPYUNREALBIRDCPP_API AFloorPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	float velocity{ 0 };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	float positionReload{ -4000 };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float new_location{ 8000 };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float offset_z{ -600 };

public:
	class AGame_mode_custom* my_game_mode{ nullptr };


public:
	FTimerHandle timer_handle;
	
	UPROPERTY(EditAnywhere)
	float timer_to_end{ 0.1 };
	
	UPROPERTY(EditAnywhere)
	bool repeat_timer{ false };

	UFUNCTION()
	void OnTimerOut();


};
