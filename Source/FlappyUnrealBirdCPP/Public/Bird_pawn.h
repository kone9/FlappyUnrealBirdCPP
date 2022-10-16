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
	bool debug_columns{ false };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float dead_impulse{ 5 };
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* mesh_Bird{ nullptr };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float impulse{ 2 };

public:
	UFUNCTION(BlueprintCallable)
	void fly();



public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* box_trigger_dead;

public:
	UFUNCTION()
		void on_component_begin_overlap(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
//////////////SONIDOS////////////////////
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* coint_sound {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ALevelSequenceActor* death_sound_level_sequence{nullptr}; //load the level_Sequencer from editor

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* fly_sound{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* pause_init_sound{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class AAmbientSound* music_nivel{ nullptr };

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class USoundBase* pause_end_sound{ nullptr };

private:
	class AGame_mode_custom* game_mode{ nullptr };

public:
	FTimerHandle timer_handle_search_game_mode;

	UFUNCTION()
	void OnTimerOut_search_game_mode();

//relacionado a la interface

private:
	class UTextRenderComponent* search_component3DTEXT_in_bluprint(FName componentTag);

	UPROPERTY(VisibleAnywhere)
	class UTextRenderComponent* scoreText_3D{ nullptr };

	UPROPERTY(VisibleAnywhere)
	class UTextRenderComponent* bestScoreTextRender{ nullptr };

private:
	int add_score();

	bool check_winner(int score);

	void to_die();

private:
	UPROPERTY(VisibleAnywhere)
	class UGameInstance_FlappyUnrealBird* my_game_instance;


public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGame_Widget> class_widget_game;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UGame_Widget* ref_widget_game{ nullptr };


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAnimMontage* my_montage; //load the montage from the editor


public:
	//No se declara el metodo y se llama desde C++, en el blueprint es un evento que se ejecuta desde esa lina
	UFUNCTION(BlueprintImplementableEvent)
	void to_dead_change_ege_from_blueprint();




//ROTAR PAJARO
public:
	UFUNCTION(BlueprintCallable)
	void rotate_bird(float& max_down_velocity, float& max_up_velocity, float& max_down_angle);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float max_down_velocity { -2000 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float max_up_velocity{ 600 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float max_down_angle{ 90 };



//////////////Pause Game UI////////////////////

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool is_pause{ false };

public:
	UFUNCTION(BlueprintCallable)
	void pause_game();

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (BindWidget))
	TSubclassOf<class UUserWidget> game_pause_ui{};

public:
	UFUNCTION(BlueprintCallable)
	void pause_create_widget();

public:
	UFUNCTION(BlueprintCallable)
	void pause_delete_widget();

private:
	class AAmbientSound* search_audio_actor_with_tag(FString tag);


//CAMBIAR DE NIVEL
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ALevelSequenceActor* Sequencer_change_level{ nullptr }; //load the level_Sequencer from editor







};








