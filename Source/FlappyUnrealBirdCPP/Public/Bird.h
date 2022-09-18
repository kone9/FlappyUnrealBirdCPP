// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Bird.generated.h"

UCLASS()
class FLAPPYUNREALBIRDCPP_API ABird : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABird();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int impulse{ 200000 };

public:
	UFUNCTION(BlueprintCallable)
		void fly();

private:
	UCharacterMovementComponent* character_movement{ nullptr };


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* box_trigger_dead;

public:
	UFUNCTION()
		void on_component_begin_overlap(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



};
