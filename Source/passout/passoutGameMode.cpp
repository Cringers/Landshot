// Copyright Epic Games, Inc. All Rights Reserved.

#include "passoutGameMode.h"
#include "passoutHUD.h"
#include "passoutCharacter.h"
#include "passoutGameState.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ApassoutGameMode::ApassoutGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ApassoutHUD::StaticClass();

	GameStateClass = ApassoutGameState::StaticClass();
}

void ApassoutGameMode::PawnDeath(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		if (SpectatingViewpointClass)
		{
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors); //This is cring and we can do better

			// Change viewtarget if any valid actor found
			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewTarget = ReturnedActors[0];

				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
				if (PC)
				{
					PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
	}

	ApassoutGameState* GS = GetGameState<ApassoutGameState>();
	if (GS)
	{
		GS->MulticastOnPawnDeath(InstigatorPawn);
	}

	EndRound();
}

void ApassoutGameMode::EndRound()
{
	UE_LOG(LogTemp, Log, TEXT("Round is over!"));
}

