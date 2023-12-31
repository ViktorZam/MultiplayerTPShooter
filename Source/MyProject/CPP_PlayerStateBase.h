// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CPP_PlayerStateBase.generated.h"

class UCPP_InstanceObject;
/**
 * 
 */
UCLASS(Blueprintable)
class MYPROJECT_API ACPP_PlayerStateBase : public APlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TMap<FString, UCPP_InstanceObject*> PlayerInfo;
};
