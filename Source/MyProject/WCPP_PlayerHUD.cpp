// Fill out your copyright notice in the Description page of Project Settings.


#include "WCPP_PlayerHUD.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
//#include "Components/ActorComponent.h"
//#include "Misc/OutputDeviceNull.h"


void UWCPP_PlayerHUD::NativeConstruct() 
{
	HorizontalBoxSlotCrosshair = CastChecked<UHorizontalBoxSlot>(Image_CenterAim->Slot);
	GetWorld()->GetTimerManager().SetTimer(TimerCheckVelocityPawn, this, &UWCPP_PlayerHUD::CheckVelocityPawn, 0.1, true);
}


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

void UWCPP_PlayerHUD::UpdateCrosshairAfterShoot()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(TimerReturnCrosshair))
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerReturnCrosshair);
	}

	HorizontalBoxSlotCrosshair->SetPadding(FMath::Clamp((HorizontalBoxSlotCrosshair->GetPadding().Top + 15), 0, MaxCrosshairPadding));

	if (GetWorld()->GetTimerManager().IsTimerActive(TimerIncreaseCrosshair))
	{

	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(TimerReturnCrosshair, this, &UWCPP_PlayerHUD::ReturnCrosshair, 0.016, true);
	}
	
	
}

void UWCPP_PlayerHUD::ReturnCrosshair()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(TimerIncreaseCrosshair))
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerReturnCrosshair);
		return;
	}

	float L_InterpPaddingCrosshair = FMath::FInterpConstantTo(HorizontalBoxSlotCrosshair->GetPadding().Top, 0, GetWorld()->GetDeltaSeconds(), 40);
	HorizontalBoxSlotCrosshair->SetPadding(L_InterpPaddingCrosshair);
	if (HorizontalBoxSlotCrosshair->GetPadding().Top == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerReturnCrosshair);
	}
}

void UWCPP_PlayerHUD::IncreaseCrosshairAtMoving()
{
	float L_InterpPaddingCrosshair = FMath::FInterpConstantTo(HorizontalBoxSlotCrosshair->GetPadding().Top, MaxCrosshairPaddingAtMoving, GetWorld()->GetDeltaSeconds(), 40);
	HorizontalBoxSlotCrosshair->SetPadding(L_InterpPaddingCrosshair);
}

void UWCPP_PlayerHUD::CheckVelocityPawn()
{
	if (GetOwningPlayer()->GetPawn())
	{

		if (GetOwningPlayer()->GetPawn()->GetVelocity().Length() != 0)
		{
			if (GetWorld()->GetTimerManager().IsTimerActive(TimerIncreaseCrosshair))
			{
			}
			else
			{

				GetWorld()->GetTimerManager().SetTimer(TimerIncreaseCrosshair, this, &UWCPP_PlayerHUD::IncreaseCrosshairAtMoving, 0.016, true);
			}
		}
		else
		{
			if (GetWorld()->GetTimerManager().IsTimerActive(TimerIncreaseCrosshair))
			{
				GetWorld()->GetTimerManager().ClearTimer(TimerIncreaseCrosshair);
			}

			if (GetWorld()->GetTimerManager().IsTimerActive(TimerReturnCrosshair))
			{
			}
			else
			{
				GetWorld()->GetTimerManager().SetTimer(TimerReturnCrosshair, this, &UWCPP_PlayerHUD::ReturnCrosshair, 0.016, true);
			}

		}
	}

}


/*
void UWCPP_PlayerHUD::InitC()
{
	FOutputDeviceNull L_OutputDeviceNull;

	TArray<UActorComponent*> L_FindedComponents;
	L_FindedComponents = GetOwningPlayer()->GetPawn()->GetComponentsByTag(UActorComponent::StaticClass(), "WeaponSystem");

	const TCHAR* L_FuncAndParams = TEXT("UpdateAmmoWidget");
	L_FindedComponents.GetData()[0]->CallFunctionByNameWithArguments(L_FuncAndParams, L_OutputDeviceNull, nullptr, true);

	L_FindedComponents = GetOwningPlayer()->GetPawn()->GetComponentsByTag(UActorComponent::StaticClass(), "StatsSystem");

	L_FuncAndParams = TEXT("UpdateStatWidget HP");
	L_FindedComponents.GetData()[0]->CallFunctionByNameWithArguments(L_FuncAndParams, L_OutputDeviceNull, nullptr, true);
}
*/








