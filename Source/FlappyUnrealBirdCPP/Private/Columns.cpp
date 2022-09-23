// Fill out your copyright notice in the Description page of Project Settings.


#include "Columns.h"
#include "Kismet/KismetMathLibrary.h"

#include <Kismet/GameplayStatics.h>
#include "Game_mode_custom.h"

#include <Engine/World.h>
#include "Engine/Engine.h"
#include "TimerManager.h"

#include "Game_mode_custom.h"
#include "Components/BoxComponent.h"

// Sets default values
AColumns::AColumns()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = Root;

	box_trigger_point = CreateDefaultSubobject<UBoxComponent>(TEXT("box_trigger_dead"));
	box_trigger_point->SetBoxExtent(FVector(64, 64, 64));
	box_trigger_point->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	box_trigger_point->SetupAttachment(RootComponent);//sino agregas esto no vas a ver las propiedades de transform position scale
}

// Called when the game starts or when spawned
void AColumns::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, UKismetMathLibrary::RandomFloatInRange(minimum_z, maximum_z)));
	
	if (GetWorld() == nullptr) return;
	GetWorld()->GetTimerManager().SetTimer(timer_handle_search_Game_mode, this, &AColumns::OnTimerOut_Search_Game_mode, 0.5, false);

	//box_trigger_point->OnComponentBeginOverlap.AddDynamic(this, &AColumns::on_component_begin_overlap_point);
}

// Called every frame
void AColumns::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (my_game_mode == nullptr) return;
	if (my_game_mode->game_over == true) return;
	if (my_game_mode->init_columns == false) return;

	velocity = my_game_mode->velocity;
	AddActorLocalOffset(FVector(0, (velocity * 1000) * -1 * DeltaTime, 0));

	
}


//get game mode despues de 1 segundo
void AColumns::OnTimerOut_Search_Game_mode()
{
	//game_mode = UGameplayStatics::GetGameMode( GetWorld() );
	if (GetWorld()->GetAuthGameMode() == nullptr)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("No se encontro el GameMode"));
		return;
	}

	my_game_mode = Cast<AGame_mode_custom>(GetWorld()->GetAuthGameMode());
}


void AColumns::on_component_begin_overlap_point(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("TENDRIA QUE SUMAR PUNTOS"));
}
