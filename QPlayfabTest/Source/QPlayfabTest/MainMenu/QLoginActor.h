// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// Playfab 관련 헤더
#include "PlayFab.h"
#include "Core/PlayFabError.h"
#include "Core/PlayFabClientDataModels.h"
// -----
#include "QLoginActor.generated.h"

UCLASS()
class QPLAYFABTEST_API AQLoginActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AQLoginActor();

protected:
	virtual void BeginPlay() override;

public:	
	void OnSuccess(const PlayFab::ClientModels::FLoginResult& Result) const;
	void OnError(const PlayFab::FPlayFabCppError& ErrorResult) const;

private:
	PlayFabClientPtr clientAPI = nullptr;
};

