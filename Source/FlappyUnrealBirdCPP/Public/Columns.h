// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Columns.generated.h"

UCLASS()
class FLAPPYUNREALBIRDCPP_API AColumns : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColumns();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float velocity{ 0 };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float minimum_z = { -1400.0 };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maximum_z = { -200.0 };

private:
	class AGame_mode_custom* my_game_mode{ nullptr };


public:
	FTimerHandle timer_handle_search_Game_mode;

	UFUNCTION()
		void OnTimerOut_Search_Game_mode();



	//in.H
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* box_trigger_point;

	UFUNCTION()
	void on_component_begin_overlap_point(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
public:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root {nullptr};


};
