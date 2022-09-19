// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird_pawn.generated.h"

UCLASS()
class FLAPPYUNREALBIRDCPP_API ABird_pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABird_pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root{ nullptr };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float dead_impulse{ 5 };
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class UStaticMeshComponent* mesh_Bird{ nullptr };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float impulse{ 2 };

public:
	UFUNCTION(BlueprintCallable)
	void fly();

public:
	UFUNCTION(BlueprintCallable)
	void pause_game();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool is_game_pause{ false };

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* box_trigger_dead;

public:
	UFUNCTION()
		void on_component_begin_overlap(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* coint_sound {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ALevelSequenceActor* death_sound_level_sequence{nullptr}; //load the level_Sequencer from editor

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* fly_sound{ nullptr };

private:
	class AGame_mode_custom* game_mode{ nullptr };

public:
	FTimerHandle timer_handle_search_game_mode;

	UFUNCTION()
	void OnTimerOut_search_game_mode();

private:
	class UTextRenderComponent* search_component3DTEXT_in_bluprint(FName componentTag);

	UPROPERTY(VisibleAnywhere)
	class UTextRenderComponent* scoreText_3D{ nullptr };

	UPROPERTY(VisibleAnywhere)
	class UTextRenderComponent* bestScoreTextRender{ nullptr };


private:
	void add_score();

private:
	UPROPERTY(VisibleAnywhere)
	class UGameInstance_FlappyUnrealBird* my_game_instance;

};
