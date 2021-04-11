// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "passoutMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PASSOUT_API UpassoutMainMenu : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Passout Main Menu")
	static void GetResolutions(TArray<FString> &resolutions);
	
};
