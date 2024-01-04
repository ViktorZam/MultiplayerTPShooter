// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBoxSlot.h"
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

	UFUNCTION(BlueprintCallable)
	void UpdateCrosshairAfterShoot();

	//UFUNCTION(BlueprintCallable)
	//void InitC();
protected:
	virtual void NativeConstruct() override;



private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TextBlock_Time;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TextBlock_Ammo;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* ProgressBar_HP;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image_CenterAim;

	UHorizontalBoxSlot* HorizontalBoxSlotCrosshair;

	const float MaxCrosshairPadding = 42;
	const float MaxCrosshairPaddingAtMoving = 20;

	FTimerHandle TimerReturnCrosshair;
	FTimerHandle TimerIncreaseCrosshair;
	FTimerHandle TimerCheckVelocityPawn;

	void ReturnCrosshair();
	void IncreaseCrosshairAtMoving();
	void CheckVelocityPawn();
};
