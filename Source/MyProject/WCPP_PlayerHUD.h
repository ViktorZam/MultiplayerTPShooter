// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WCPP_PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UWCPP_PlayerHUD : public UUserWidget
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable)
	void UpdateTimeWidgetComponent(int CurrentTime);

	UFUNCTION(BlueprintCallable)
	void UpdateAmmoWidgetComponent(int CurrentInMagazine, int InSelf);

	UFUNCTION(BlueprintCallable)
	void UpdateHPWidgetComponent(float CurrentHP, float MaxHP);


private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TextBlock_Time;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TextBlock_Ammo;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* ProgressBar_HP;

};
