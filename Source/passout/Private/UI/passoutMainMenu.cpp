// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/passoutMainMenu.h"

#include "Kismet/KismetSystemLibrary.h"

void UpassoutMainMenu::GetResolutions(TArray<FString> &resolutions)
{
    TArray<FIntPoint> ResolutionPoints;
    bool GetResolutionsSuccess = UKismetSystemLibrary::GetSupportedFullscreenResolutions(ResolutionPoints);

    for (FIntPoint res : ResolutionPoints)
    {
        FString resolution = FString::Printf(TEXT("%dx%d"), res.X, res.Y);
        resolutions.Push(resolution);
    }
}
