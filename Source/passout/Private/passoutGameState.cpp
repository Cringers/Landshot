// Fill out your copyright notice in the Description page of Project Settings.


#include "passoutGameState.h"

void ApassoutGameState::MulticastOnPawnDeath_Implementation(APawn* InstigatorPawn)
{
	APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
	if (PC)
	{
		InstigatorPawn->DisableInput(PC);
	}
}
