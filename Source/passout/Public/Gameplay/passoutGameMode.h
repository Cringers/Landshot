// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "passoutGameMode.generated.h"

UCLASS(minimalapi)
class ApassoutGameMode : public AGameModeBase
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
	TSubclassOf<AActor> SpectatingViewpointClass;

public:
	ApassoutGameMode();

	UFUNCTION()
	void PawnDeath(APawn* InstigatorPawn);

private:
	UFUNCTION()
	void EndRound();

	virtual void HandleStartingNewPlayer_Implementation(APlayerController*) override;

};



