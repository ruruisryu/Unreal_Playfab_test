// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/QLoginActor.h"
#include "Core/PlayFabClientAPI.h"

AQLoginActor::AQLoginActor()
{
 	PrimaryActorTick.bCanEverTick = true;

}

void AQLoginActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetMutableDefault<UPlayFabRuntimeSettings>()->TitleId = TitleId;
    
	clientAPI = IPlayFabModuleInterface::Get().GetClientAPI();
    dataAPI = IPlayFabModuleInterface::Get().GetDataAPI();

	// NDM에서는 익명 로그인 메커니즘을 사용하기 위해 LoginWithCustomID로 로그인을 진행하지만,
	// 이후에는 스팀 출시를 고려해 LoginWithSteamRequest로 로그인 진행
	PlayFab::ClientModels::FLoginWithCustomIDRequest request;
	request.CustomId = CustomId;
	request.CreateAccount = true;

	// login 시도
	clientAPI->LoginWithCustomID(request,
		PlayFab::UPlayFabClientAPI::FLoginWithCustomIDDelegate::CreateUObject(this, &AQLoginActor::OnLoginSuccess),
		PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &AQLoginActor::OnError)
	);
}

// LoginWithCustomID 호출이 성공했을 때 호출되며, 로그인 결과를 처리하고 데이터를 요청합니다.
void AQLoginActor::OnLoginSuccess(const PlayFab::ClientModels::FLoginResult& Result)
{
	UE_LOG(LogTemp, Log, TEXT("------------------------------------------------\n"));
	UE_LOG(LogTemp, Log, TEXT("Login call succeeded."));
	UE_LOG(LogTemp, Log, TEXT("your Playfab ID is %s"), *Result.PlayFabId);
	UE_LOG(LogTemp, Log, TEXT("Is your account newly created? : %s"), Result.NewlyCreated ? TEXT("Yes") : TEXT("No"));
	
	LoggedIn = true;
	
	// dataAPI 호출
	PlayFab::DataModels::FGetObjectsRequest dataRequest;
	dataRequest.AuthenticationContext = Result.AuthenticationContext;
	dataRequest.Entity.Id = Result.EntityToken->Entity->Id;
	dataRequest.Entity.Type = Result.EntityToken->Entity->Type;

	dataAPI->GetObjects(
		dataRequest,
		PlayFab::UPlayFabDataAPI::FGetObjectsDelegate::CreateUObject(this, &AQLoginActor::OnGetObjectsSuccess),
		PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &AQLoginActor::OnError)
	);
}

void AQLoginActor::OnGetObjectsSuccess(const PlayFab::DataModels::FGetObjectsResponse& Result)
{
	// 서버에서 반환된 데이터를 저장하고 처리합니다.
	PlayerData = Result.Objects;
	DataLoaded = true;
	UE_LOG(LogTemp, Log, TEXT("Player data loaded."));
}

// login 실패
void AQLoginActor::OnError(const PlayFab::FPlayFabCppError& ErrorResult) const
{
	UE_LOG(LogTemp, Error, TEXT("Something went wrong with your first API call.\nHere's some debug information:\n%s"), *ErrorResult.GenerateErrorReport());
}

