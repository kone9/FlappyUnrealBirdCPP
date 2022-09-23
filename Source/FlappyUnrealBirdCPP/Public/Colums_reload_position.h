// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Colums_reload_position.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLAPPYUNREALBIRDCPP_API UColums_reload_position : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UColums_reload_position();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


//colums parameters
private:
	AActor* columns{ nullptr };

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float diferencia_posicion{ 0 };

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float minimum_z = { -1400.0 };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maximum_z = { -200.0 };


//search game mode
public:
	class AGame_mode_custom* my_game_mode{ nullptr };

public:
	FTimerHandle timer_handle_search_Game_mode;

	UFUNCTION()
	void OnTimerOut_Search_Game_mode();


//ref box collision
public:
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* ref_box_collision;

		
};
