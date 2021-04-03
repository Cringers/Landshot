// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/passoutKillZone.h"
#include "Components/BoxComponent.h"
#include "Gameplay/passoutCharacter.h"
#include "Gameplay/passoutGameMode.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ApassoutKillZone::ApassoutKillZone()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;

	OverlapComp->SetHiddenInGame(false);

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ApassoutKillZone::HandleOverlap);
}

void ApassoutKillZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ApassoutCharacter* MyPawn = Cast<ApassoutCharacter>(OtherActor);
	if (MyPawn == nullptr)
	{
		return;
	}

	ApassoutGameMode* GM = Cast<ApassoutGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->PawnDeath(MyPawn);
	}

	UGameplayStatics::PlaySound2D(this, DeathSound);

	UE_LOG(LogTemp, Log, TEXT("Overlapped with kill zone!"));

}

