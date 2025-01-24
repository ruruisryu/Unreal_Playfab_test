// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// Playfab 관련 헤더
#include "PlayFab.h"
#include "Core/PlayFabError.h"
#include "Core/PlayFabClientDataModels.h"
#include "Core/PlayFabClientAPI.h"
#include "Core/PlayFabDataAPI.h"
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
	UPROPERTY(EditAnywhere, config, Category = Settings)
	FString TitleId = TEXT("1381A");

	UPROPERTY(EditAnywhere, config, Category = Settings)
	FString CustomId = TEXT("ExampleCustomId");
	
	void OnLoginSuccess(const PlayFab::ClientModels::FLoginResult& Result);
	void OnGetObjectsSuccess(const PlayFab::DataModels::FGetObjectsResponse& Result);
	void OnError(const PlayFab::FPlayFabCppError& ErrorResult) const;

public:
	bool LoggedIn = false;
	bool DataLoaded = false;

	PlayFabClientPtr clientAPI = nullptr;
	PlayFabDataPtr dataAPI = nullptr;

	TMap<FString, PlayFab::DataModels::FObjectResult> PlayerData;
};

