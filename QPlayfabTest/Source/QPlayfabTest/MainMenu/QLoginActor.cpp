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
	
	// TODO 
	// TitleId 별도 저장 필요
	GetMutableDefault<UPlayFabRuntimeSettings>()->TitleId = TEXT("1381A");
    
	clientAPI = IPlayFabModuleInterface::Get().GetClientAPI();

	// NDM에서는 익명 로그인 메커니즘을 사용하기 위해 LoginWithCustomID로 로그인을 진행하지만,
	// 이후에는 스팀 출시를 고려해 LoginWithSteamRequest로 로그인 진행
	PlayFab::ClientModels::FLoginWithCustomIDRequest request;
	// TODO 
	// CustomId 생성 부분 수정 필요
	request.CustomId = TEXT("GettingStartedGuide");	
	request.CreateAccount = true;

	// login
	clientAPI->LoginWithCustomID(request,
		PlayFab::UPlayFabClientAPI::FLoginWithCustomIDDelegate::CreateUObject(this, &AQLoginActor::OnSuccess),
		PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &AQLoginActor::OnError)
	);
}

// login 성공
void AQLoginActor::OnSuccess(const PlayFab::ClientModels::FLoginResult& Result) const
{
	UE_LOG(LogTemp, Log, TEXT("Congratulations, you made your first successful API call!"));
	
	if (Result.InfoResultPayload && Result.InfoResultPayload->PlayerProfile && Result.InfoResultPayload->AccountInfo) return;
	
	UE_LOG(LogTemp, Log, TEXT("your Playfab ID is %s"), *Result.PlayFabId);
	UE_LOG(LogTemp, Log, TEXT("Is your account newly created? : %s"), Result.NewlyCreated ? TEXT("Yes") : TEXT("No"));
	/*
	UE_LOG(LogTemp, Log, TEXT("PlayerProfile->Displayname is %s"), *Result.InfoResultPayload->PlayerProfile->DisplayName);
	UE_LOG(LogTemp, Log, TEXT("AccountInfo->Username is %s"), *Result.InfoResultPayload->AccountInfo->Username);
	*/
}

// login 실패
void AQLoginActor::OnError(const PlayFab::FPlayFabCppError& ErrorResult) const
{
	UE_LOG(LogTemp, Error, TEXT("Something went wrong with your first API call.\nHere's some debug information:\n%s"), *ErrorResult.GenerateErrorReport());
}

