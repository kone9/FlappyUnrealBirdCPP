// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird_pawn.h"

#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>


#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>
#include "TimerManager.h"
#include "Game_mode_custom.h"


//.CPP
#include <LevelSequenceActor.h>
#include <LevelSequencePlayer.h>
#include <MovieSceneSequencePlayer.h>




// Sets default values
ABird_pawn::ABird_pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = Root;

	

	mesh_Bird = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh_Bird"));
	mesh_Bird->SetSimulatePhysics(true);
	//RootComponent = mesh_Bird;
	mesh_Bird->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

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
	if (GetWorld() == nullptr) return;
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("LA COLISION DEL PAJARO CHOCO CON ALGO"));


	if (OtherComp == nullptr) return;
	if( OtherComp->ComponentHasTag( TEXT("trigger_point") ) )//si colisiono con puntaje
	{
		if (coint_sound == nullptr) return;
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("SUMO PUNOS"));
		UGameplayStatics::PlaySound2D(GetWorld(), coint_sound);
	}
	else//si colisiono con obstaculo
	{
		DisableInput( UGameplayStatics::GetPlayerController( GetWorld(),0 ) );
		if(game_mode != nullptr) game_mode->game_over = true;

		//mesh_Bird->AddRadialImpulse(GetActorLocation(), 1000000, 1000000,ERadialImpulseFalloff::RIF_Linear);
		//mesh_Bird->AddImpulse(FVector::UpVector * (dead_impulse * 1000000));
		mesh_Bird->AddImpulse(FVector((dead_impulse * 1000000), (dead_impulse * 100000), (dead_impulse * 1000000)));
		//Beginplay example
		
		if (death_sound_level_sequence == nullptr) return;
		death_sound_level_sequence->SequencePlayer->Play();
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
}

