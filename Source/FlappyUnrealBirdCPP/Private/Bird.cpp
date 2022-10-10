// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"
#include "Components/BoxComponent.h"

// Sets default values
ABird::ABird()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	box_trigger_dead = CreateDefaultSubobject<UBoxComponent>(TEXT("box_trigger_dead"));
	box_trigger_dead->SetBoxExtent(FVector(64, 64, 64));
	box_trigger_dead->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();
	character_movement = GetCharacterMovement();

	if (box_trigger_dead == nullptr) return;
	box_trigger_dead->OnComponentBeginOverlap.AddDynamic(this, &ABird::on_component_begin_overlap);
}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent == nullptr) return;
	PlayerInputComponent->BindAction("Fly_key", IE_Pressed, this, &ABird::fly);

}


//para hacer volar con el input
void ABird::fly()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Tendria que volar"));

	if (character_movement == nullptr) return;

	Jump();
	character_movement->AddImpulse(FVector::UpVector * impulse);
}


void ABird::on_component_begin_overlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}