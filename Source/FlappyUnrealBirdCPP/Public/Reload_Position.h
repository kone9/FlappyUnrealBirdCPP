// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Reload_Position.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLAPPYUNREALBIRDCPP_API UReload_Position : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UReload_Position();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	AActor* platform{ nullptr };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float positionReload{ -4000 };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float new_location{ 8000 };

};
