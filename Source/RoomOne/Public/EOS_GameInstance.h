// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Http.h"
#include "EOS_GameInstance.generated.h"


USTRUCT(BlueprintType)
struct FBlueprintSessionResultCustom
{
	GENERATED_USTRUCT_BODY()
	
	FOnlineSessionSearchResult OnlineResult;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBlueprintFindSessionsResultDelegate, const TArray<FBlueprintSessionResultCustom>&, Results);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSheetDataReceived, const FString&, Response);

/**
 * 
 */
UCLASS()
class ROOMONE_API UEOS_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UEOS_GameInstance();
	virtual void Init() override;

	using UGameInstance::JoinSession; //Added because linux is linuxing
	
	UFUNCTION(BlueprintCallable, Category = "EOS")
	void Login(bool dev);
	void OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful,  const FUniqueNetId& UserId, const FString& Error);
	
	UFUNCTION(BlueprintCallable, Category = "EOS")
	void ForceLogout();

	UFUNCTION(BlueprintCallable, Category = "EOS")
	void CreateSession();
	void OnCreateSessionComplete(FName Name, bool bArg);
	UPROPERTY(BlueprintReadOnly, Category="EOS")
	FString CurrentLobbyId;

	UFUNCTION(BlueprintCallable, Category = "EOS")
	void DestroySession();
	void OnDestroySessionComplete(FName Name, bool bArg);

	UFUNCTION(BlueprintCallable, Category="EOS")
	void DestroySessionOnClient();
	
	UFUNCTION(BlueprintCallable, Category = "EOS")
	void FindSessions();
	TSharedPtr<FOnlineSessionSearch> SearchSettings;
	void OnFindSessionsComplete(bool bArg);
	UPROPERTY(BlueprintAssignable, Category = "EOS|Sessions")
	FBlueprintFindSessionsResultDelegate OnFindSessionsSuccess;

	

	UFUNCTION(BlueprintCallable, Category = "EOS")
	void JoinSession(const FBlueprintSessionResultCustom& Result);
	void OnJoinSessionComplete(FName Name, EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION(BlueprintCallable, Category="EOS")
	FString GetLobbyId(const FBlueprintSessionResultCustom& Result) const;
	
	
	//Save
	void TrySilentLogin();

	UFUNCTION(BlueprintCallable, Category = "Badges")
	void RequestBadgeSheet();

	UPROPERTY(BlueprintAssignable, Category = "Badges")
	FOnSheetDataReceived OnBadgeDataReceived;
	

	UPROPERTY(BlueprintReadWrite, Category="Game")
	APawn* ControlledPawn;

	UFUNCTION(BlueprintCallable, Category = "GameCode")
	void AddGameCode(const FString& Code, const FString& LobbyId);

	UFUNCTION(BlueprintCallable, Category = "GameCode")
	void RemoveGameCode(const FString& Code);

	UFUNCTION(BlueprintCallable, Category = "GameCode")
	void RequestGameCodes();

	UPROPERTY(BlueprintAssignable, Category = "GameCode")
	FOnSheetDataReceived OnGameDataReceived;
	
	
private:
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) const;
	void OnGameCodeResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) const;
	void OnSessionInviteAccepted(
	const bool bWasSuccessful,
	int32 LocalUserNum,
	TSharedPtr<const FUniqueNetId> InvitingPlayer,
	const FOnlineSessionSearchResult& SessionToJoin);
	
	

protected:
	class IOnlineSubsystem* OnlineSubsystem;

	TArray<FOnlineSessionSearchResult> CachedResults;
	
	UPROPERTY(BlueprintReadOnly, Category="EOS")
	bool bIsLoggedIn;

	UPROPERTY(BlueprintReadOnly, Category="EOS")
	FString playerName;

	UPROPERTY(BlueprintReadOnly, Category="EOS")
	FString userId;
	

};



