// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "passoutGameState.generated.h"

UCLASS()
class PASSOUT_API ApassoutGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnPawnDeath(APawn* InstigatorPawn);

};
