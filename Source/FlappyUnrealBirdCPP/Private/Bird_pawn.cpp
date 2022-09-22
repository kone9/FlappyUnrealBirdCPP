// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird_pawn.h"


//componentes unreal clases
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"

//unreal clases
#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"

//game mode
#include "Game_mode_custom.h"


//lvel sequencer
#include <LevelSequenceActor.h>
#include <LevelSequencePlayer.h>
#include <MovieSceneSequencePlayer.h>

//text render 3D
#include "Components/TextRenderComponent.h"

//game mde custom
#include "GameInstance_FlappyUnrealBird.h"

//user widget
#include "Game_Widget.h"
#include "Components/TextBlock.h"

//anim montage
#include "Animation/AnimMontage.h" //If you are not in the character class you may have to import the library




// Sets default values
ABird_pawn::ABird_pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create root component
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = Root;

	//create skeletan mesh component
	mesh_Bird = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mesh_Bird"));
	mesh_Bird->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	mesh_Bird->SetupAttachment(RootComponent);//sino agregas esto no vas a ver las propiedades de transform position scale
	mesh_Bird->SetSimulatePhysics(true);

	//create box trigger component
	box_trigger_dead = CreateDefaultSubobject<UBoxComponent>(TEXT("box_trigger_dead"));
	box_trigger_dead->SetBoxExtent(FVector(64, 64, 64));
	box_trigger_dead->AttachToComponent(mesh_Bird, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ABird_pawn::BeginPlay()
{
	Super::BeginPlay();

	if (box_trigger_dead == nullptr) return;
	box_trigger_dead->OnComponentBeginOverlap.AddDynamic(this, &ABird_pawn::on_component_begin_overlap);

	//begin play		
	if (GetWorld() == nullptr) return;
	GetWorld()->GetTimerManager().SetTimer(timer_handle_search_game_mode, this, &ABird_pawn::OnTimerOut_search_game_mode, 0.1, false);
	mesh_Bird->SetSimulatePhysics(false);

	//get score text 3D en tabla final
	scoreText_3D = search_component3DTEXT_in_bluprint(TEXT("scoreText_3D"));
	bestScoreTextRender = search_component3DTEXT_in_bluprint(TEXT("BestScoreTextRender"));

	//create widget from player

	if (class_widget_game == nullptr) return;
	ref_widget_game = Cast< UGame_Widget>( CreateWidget(GetWorld(), class_widget_game) );
	if (ref_widget_game == nullptr) return;
	ref_widget_game->AddToViewport();
}

// Called every frame
void ABird_pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABird_pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent == nullptr) return;
	PlayerInputComponent->BindAction("Fly_key", IE_Pressed, this, &ABird_pawn::fly);

	PlayerInputComponent->BindAction("pause_key_space", IE_Pressed, this, &ABird_pawn::pause_game).bExecuteWhenPaused = true;
	
}

//para volar
void ABird_pawn::fly()
{
	if (game_mode->init_columns == false)//para activar fisicas y hacer que las columnas se muevan
	{
		mesh_Bird->SetSimulatePhysics(true);
		game_mode->init_columns = true;
	}

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("PRESIONE LA TECLA VOLAR"));
	mesh_Bird->AddImpulse(FVector::UpVector * (impulse * 1000000) );

	//mesh_Bird->AddTorque(FVector(50, 0, 0));

	//play montaje
	//if (my_montage == nullptr) return;//si hay un montage
	//mesh_Bird->PlayAnimation(my_montage,false);
	//
	if (fly_sound == nullptr) return;
	UGameplayStatics::PlaySound2D(GetWorld(), fly_sound);
}

//crea un pause en el juego
void ABird_pawn::pause_game()
{
	if (GetWorld() == nullptr) return;

	is_game_pause = !is_game_pause;
	
	const bool my_test_bool = is_game_pause;
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("IS PAUSE GAME: %s"), my_test_bool ? TEXT("true") : TEXT("false")));
	
	UGameplayStatics::SetGamePaused(GetWorld(), is_game_pause);
}

//box collision para morir
void ABird_pawn::on_component_begin_overlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (game_mode->game_over == true) return;
	if (OtherComp == nullptr) return;
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("LA COLISION DEL PAJARO CHOCO CON ALGO"));

	if( OtherComp->ComponentHasTag( TEXT("trigger_point") ) )//si colisiono con puntaje
	{
		add_score();
	}
	else//si colisiono con obstaculo
	{
		to_die();
		to_dead_change_ege_from_blueprint();
	}

	
}




//get game mode after 1 second
void ABird_pawn::OnTimerOut_search_game_mode()
{
	//game_mode = UGameplayStatics::GetGameMode( GetWorld() );
	if (GetWorld()->GetAuthGameMode() == nullptr)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("No se encontro el GameMode"));
		return;
	}

	game_mode = Cast<AGame_mode_custom>(GetWorld()->GetAuthGameMode());
	my_game_instance = Cast<UGameInstance_FlappyUnrealBird>( UGameplayStatics::GetGameInstance(GetWorld()) ) ;
}


//busca los textos que se encuentran dentro de los componetes en los blueprint
UTextRenderComponent* ABird_pawn::search_component3DTEXT_in_bluprint(FName componentTag)
{

	//Begin play example
	//search and get actor with tag
	TArray<AActor*> actor_with_tag{};
	FName tag_actor = TEXT("tablero_end_Blueprint");// add tag actor here
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), tag_actor, actor_with_tag);
	AActor* actor = actor_with_tag[0];

	if (actor == nullptr) return nullptr;

	UTextRenderComponent* text_spatial = Cast<UTextRenderComponent>( actor->GetComponentsByTag( UTextRenderComponent::StaticClass(), componentTag)[0] );

	if (text_spatial == nullptr)
	{
		return nullptr;

	}
	else
	{
		return text_spatial;
	}


}

//agrega puntaje al tablero principal y a la interface del juego
void ABird_pawn::add_score()
{
	if (game_mode == nullptr) return;
	if (scoreText_3D == nullptr) return;
	if (my_game_instance == nullptr) return;
	if (bestScoreTextRender == nullptr) return;
	if (coint_sound == nullptr) return;
	if (ref_widget_game == nullptr) return;

	UGameplayStatics::PlaySound2D(GetWorld(), coint_sound);

	game_mode->score += 1;
	int score = game_mode->score;

	FString score_String{ FString::FromInt(score) };
	FName scorefname{ FName(*score_String) };
	scoreText_3D->SetText( FText::FromString(score_String) );

	if (score > my_game_instance->max_score)
	{
		my_game_instance->max_score = score;
		bestScoreTextRender->SetText(FText::FromString( score_String) );
	}

	ref_widget_game->score_text->SetText(FText::FromString(score_String));
	

	const int int_to_print = score;
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("SUMA PUNTOS PUNTAJE ACTUAL = %i"), int_to_print));
}


//cuando muere desactiva viewport, activa sonido morir, activa level sequencer morir, agrega impulso morir, game over en game_mode
void ABird_pawn::to_die()
{
	if (GetWorld() == nullptr) return;
	if (ref_widget_game == nullptr) return;
	ref_widget_game->RemoveFromViewport();

	DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (game_mode != nullptr) game_mode->game_over = true;

	//mesh_Bird->AddRadialImpulse(GetActorLocation(), 1000000, 1000000,ERadialImpulseFalloff::RIF_Linear);
	//mesh_Bird->AddImpulse(FVector::UpVector * (dead_impulse * 1000000));
	mesh_Bird->AddImpulse(FVector((dead_impulse * 1000000), (dead_impulse * 100000), (dead_impulse * 1000000)));
	//Beginplay example

	if (death_sound_level_sequence == nullptr) return;
	death_sound_level_sequence->SequencePlayer->Play();
}

