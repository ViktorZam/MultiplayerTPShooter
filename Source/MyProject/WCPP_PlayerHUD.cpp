// Fill out your copyright notice in the Description page of Project Settings.


#include "WCPP_PlayerHUD.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UWCPP_PlayerHUD::UpdateTimeWidgetComponent(int CurrentTime) 
{
	int L_Minutes = CurrentTime / 60;
	int L_Seconds = fmod(CurrentTime, 60);

	FString L_Time;
	L_Time.Append(FString::FromInt(L_Minutes));
	if (L_Seconds < 10)
	{
		L_Time.Append(":0");
	}
	else
	{
		L_Time.Append(":");
	}
	L_Time.Append(FString::FromInt(L_Seconds));

	
	TextBlock_Time->SetText(FText::FromString(L_Time));

}


void UWCPP_PlayerHUD::UpdateAmmoWidgetComponent(int CurrentInMagazine, int InSelf)
{
	FString L_Ammo;

	L_Ammo.Append(FString::FromInt(CurrentInMagazine));
	L_Ammo.Append(" / ");
	L_Ammo.Append(FString::FromInt(InSelf));

	TextBlock_Ammo->SetText(FText::FromString(L_Ammo));
}

void UWCPP_PlayerHUD::UpdateHPWidgetComponent(float CurrentHP, float MaxHP)
{
	ProgressBar_HP->SetPercent((1 / MaxHP) * CurrentHP);
}



