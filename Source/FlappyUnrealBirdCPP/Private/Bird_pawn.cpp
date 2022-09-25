// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird_pawn.h"


//componentes unreal clases
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"

//unreal clases
#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>
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

//matematic
#include "Kismet/KismetMathLibrary.h"


//pause menu
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Pause_exit_Game.h"




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

	rotate_bird(max_down_velocity, max_up_velocity, max_down_angle);

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
	if (game_mode == nullptr) return;
	if (game_mode->game_over == true) return;
	
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


//crea un pause en el juego cuando se presiona la tecla pause
void ABird_pawn::pause_game()
{
	//create UI pause cuando presiono start
	if (add_pause_menu == false)
	{
		pause_create_widget();
	}
	else // delete ui pause
	{
		pause_delete_widget();
	}
}


//crea un widget de pause
void ABird_pawn::pause_create_widget()
{
	if (GetWorld() == nullptr) return;
	if (pause_init_sound == nullptr) return;

	add_pause_menu = true;

	//create widget pause
	UUserWidget* new_pause_UI = CreateWidget(GetWorld(), game_pause_ui);
	if (new_pause_UI == nullptr) return;
	new_pause_UI->AddToViewport();

	//add pause
	UGameplayStatics::SetGamePaused(GetWorld(), add_pause_menu);
	
	//input in UI
	/*APlayerController* playercontroller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playercontroller == nullptr) return;
	UWidgetBlueprintLibrary::SetInputMode_UIOnly(playercontroller, new_pause_UI);*/
	
	UGameplayStatics::PlaySound2D(GetWorld(), pause_init_sound);
}


//si existe borra el widget pause creado anteriormente
void ABird_pawn::pause_delete_widget()
{
	if (GetWorld() == nullptr) return;
	if (pause_end_sound == nullptr) return;

	//delete pause
	add_pause_menu = false;
	UGameplayStatics::SetGamePaused(GetWorld(), add_pause_menu);

	//search widget
	TArray<UUserWidget* > founds_widget;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), founds_widget, UPause_exit_Game::StaticClass());
	UUserWidget* pause_ui = founds_widget[0];

	if (pause_ui == nullptr) return;
	
	APlayerController* playercontroller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playercontroller == nullptr) return;
	UWidgetBlueprintLibrary::SetInputMode_GameOnly((playercontroller));

	pause_ui->RemoveFromParent();

	UGameplayStatics::PlaySound2D(GetWorld(), pause_end_sound);
}

//box collision para morir
void ABird_pawn::on_component_begin_overlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (game_mode == nullptr) return;
	if (game_mode->game_over == true) return;
	if (OtherComp == nullptr) return;
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("LA COLISION DEL PAJARO CHOCO CON ALGO"));

	if( OtherComp->ComponentHasTag( TEXT("trigger_point") ) )//si colisiono con puntaje
	{
		add_score();
		OtherComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);//desactivo colision para que no vuelva a dar puntos hasta que reinicie posicion columna
	}
	else//si colisiono con obstaculo
	{
		to_die();
		to_dead_change_ege_from_blueprint();//esto es un evento C++ hacia un blueprint, cambio lo que hace desde el blueprint
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

	//DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (game_mode != nullptr) game_mode->game_over = true;

	mesh_Bird->AddImpulse(FVector((dead_impulse * 1000000), (dead_impulse * 100000), (dead_impulse * 1000000)));

	if (death_sound_level_sequence == nullptr) return;
	death_sound_level_sequence->SequencePlayer->Play();
}



//rota el pajaro en un intervalo dependiendo la velocidad de caida
void ABird_pawn::rotate_bird(float& max_down_velocity, float& max_up_velocity, float& max_down_angle)
{

	if (mesh_Bird == nullptr) return;
	if (game_mode == nullptr) return;
	if (game_mode->game_over == true) return;
 	if (mesh_Bird->IsSimulatingPhysics() == false) return;

	float current_velocity = UKismetMathLibrary::Clamp(mesh_Bird->GetComponentVelocity().Z, max_down_velocity, max_up_velocity);//aseguro que la velocidad en el eje Z va a estar entre -2000 y 500 por default

	//angulo que va a tener el pajaro basandose en la velocidad de caida.. 
	//Se divide la velocidad actual entre la velocidad maxima, eso nos da la proporcion entre velocidad actual y velocidad maxima que es de 0 a 1000
	//si dividimos la velocidad actual por la maxima velocidad y current velocity es cero, max entonces da cero
	//despues lo multiplicamos por el angulo para obtener un angulo de "0" 
	// si la velocidad actual es igual a la máxima y lo multiplicamos por el angulo tenemos la rotación actual en 90
	//asi en todos los keyframes intermedios para tener los angulos intermedios
	float angle = (current_velocity / max_down_velocity) * max_down_angle;

	FRotator new_rotation = FRotator(0, 0, angle);//guardo la rotacion en angulo

	mesh_Bird->SetWorldRotation(new_rotation,false,nullptr,ETeleportType::TeleportPhysics);//roto el pajaro
	

	const float float_to_print = current_velocity;
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("ANGULO por velocity Z: %f"), float_to_print));
}

