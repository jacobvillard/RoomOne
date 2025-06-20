// Fill out your copyright notice in the Description page of Project Settings.


#include "EOS_GameInstance.h"

#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Online/OnlineSessionNames.h"
#include "eos_sdk.h"
#include "eos_auth.h"
#include "EOSShared.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"



const FName SessionName = FName("Test_Session");

UEOS_GameInstance::UEOS_GameInstance()
{
	bIsLoggedIn = false;
}

void UEOS_GameInstance::Init()
{
	Super::Init();
	
	OnlineSubsystem = IOnlineSubsystem::Get();

	TrySilentLogin();
	
}

void UEOS_GameInstance::TrySilentLogin()
{
	if (!OnlineSubsystem)          { UE_LOG(LogTemp, Warning, TEXT("SL: no OSS"));          return;   }
	IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface();
	if (!Identity.IsValid())       { UE_LOG(LogTemp, Warning, TEXT("SL: no Identity"));   return; }


	FOnlineAccountCredentials Creds;
	Creds.Type  = FString("persistentauth");      // EOS expects this literal
	Creds.Token = FString(); 
	Creds.Id    = FString();                    // not used

	Identity->OnLoginCompleteDelegates->AddUObject(this, &UEOS_GameInstance::OnLoginComplete);
	bIsLoggedIn = Identity->Login(0, Creds); // returns true if login is in progress
	UE_LOG(LogTemp, Log, TEXT("SL: Login() queued = %d"), bIsLoggedIn);
}


void UEOS_GameInstance::Login(bool dev)
{
	TrySilentLogin();

	if (OnlineSubsystem)
	{
		if(dev)
		{
			if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
			{
				FOnlineAccountCredentials Credentials;
				Credentials.Id = FString("127.0.0.1:8081");
				Credentials.Token = FString("CredDark");
				Credentials.Type = FString("developer");

				Identity->OnLoginCompleteDelegates->AddUObject(this, &UEOS_GameInstance::OnLoginComplete);
				Identity->Login(0, Credentials);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Online identity interface is not available."));
			}
		}
		else
		{
			if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
			{
				FOnlineAccountCredentials Credentials;
				Credentials.Id = FString();
				Credentials.Token = FString();
				Credentials.Type = FString("accountportal");

				Identity->OnLoginCompleteDelegates->AddUObject(this, &UEOS_GameInstance::OnLoginComplete);
				Identity->Login(0, Credentials);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Online identity interface is not available."));
			}
		}
		
	}
		
}

void UEOS_GameInstance::OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	bIsLoggedIn = bWasSuccessful;
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Login successful for user: %s"), *UserId.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Login failed: %s"), *Error);
	}
	
	if (OnlineSubsystem)
	{
		if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
		{
			Identity->ClearOnLoginCompleteDelegates(0, this);
			playerName = Identity->GetPlayerNickname(0);
			TSharedPtr<const FUniqueNetId> NetId = Identity->GetUniquePlayerId(0);
			if (NetId.IsValid())
			{
				userId = NetId->ToString();
				UE_LOG(LogTemp, Log, TEXT("Got user ID: %s"), *userId);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to get Unique Player ID"));
			}
			UE_LOG(LogTemp, Error, TEXT("Fetched DisplayName: %s"), *playerName);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Online identity interface is not available."));
		}
	}
}

void UEOS_GameInstance::ForceLogout()
{
	
	if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
	{
		Identity->Logout(0);
	}

	bIsLoggedIn = false;
}



void UEOS_GameInstance::CreateSession()
{
	if (bIsLoggedIn )
	{
		if(OnlineSubsystem)
		{
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{
				FOnlineSessionSettings SessionSettings;
				SessionSettings.bIsDedicated = false;
				SessionSettings.bShouldAdvertise = true;
				SessionSettings.bIsLANMatch = false;
				SessionSettings.NumPublicConnections = 5;
				SessionSettings.bAllowJoinInProgress = true;
				SessionSettings.bAllowJoinViaPresence = true;
				SessionSettings.bUsesPresence = true;
				SessionSettings.bUseLobbiesIfAvailable = true;

				SessionSettings.Set(SEARCH_KEYWORDS, FString("DarkCred"), EOnlineDataAdvertisementType::ViaOnlineService);

				SessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UEOS_GameInstance::OnCreateSessionComplete);
				SessionPtr->CreateSession(0, SessionName, SessionSettings);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online session interface is not available."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online subsystem is not available."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create session: User is not logged in"));
	}
}

void UEOS_GameInstance::OnCreateSessionComplete(FName Name, bool bArg)
{
	if (bArg)
	{
		UE_LOG(LogTemp, Log, TEXT("Session '%s' created successfully."), *Name.ToString());
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			if (FNamedOnlineSession* Named = SessionPtr->GetNamedSession(Name))
			{
				CurrentLobbyId = Named->GetSessionIdStr();           // cache it for anyone who asks
				UE_LOG(LogTemp, Log, TEXT("Created lobby ID: %s"), *CurrentLobbyId);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create session '%s'."), *Name.ToString());
	}

	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->ClearOnCreateSessionCompleteDelegates(this);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Online session interface is not available."));
		}
	}
}

void UEOS_GameInstance::DestroySession()
{
	if (bIsLoggedIn )
	{
		if(OnlineSubsystem)
		{
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{
				SessionPtr->OnDestroySessionCompleteDelegates.AddUObject(this, &UEOS_GameInstance::OnDestroySessionComplete);
				SessionPtr->DestroySession(SessionName);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online session interface is not available."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online subsystem is not available."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create session: User is not logged in"));
	}
}

void UEOS_GameInstance::OnDestroySessionComplete(FName Name, bool bArg)
{
	if(bArg)
	{
		UE_LOG(LogTemp, Log, TEXT("Session '%s' destroyed successfully."), *Name.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to destroy session '%s'."), *Name.ToString());
	}

	
	if(OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->ClearOnDestroySessionCompleteDelegates(this);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online session interface is not available."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online subsystem is not available."));
	}

	
}

void UEOS_GameInstance::FindSessions()
{
	if (bIsLoggedIn )
	{
		if(OnlineSubsystem)
		{
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{
				SearchSettings = MakeShareable(new FOnlineSessionSearch());
				SearchSettings->MaxSearchResults = 5000;
				SearchSettings->QuerySettings.Set(SEARCH_KEYWORDS, FString("DarkCred"), EOnlineComparisonOp::Equals);
				SearchSettings->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
				SessionPtr->OnFindSessionsCompleteDelegates.AddUObject(this, &UEOS_GameInstance::OnFindSessionsComplete);
				SessionPtr->FindSessions(0, SearchSettings.ToSharedRef());
				
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online session interface is not available."));
			}	
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online subsystem is not available."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create session: User is not logged in"));
	}
}

void UEOS_GameInstance::OnFindSessionsComplete(bool bArg)
{
	if(bArg)
	{
		UE_LOG(LogTemp, Log, TEXT("Find sessions completed successfully."));
		UE_LOG(LogTemp, Log, TEXT("Found %d sessions."), SearchSettings->SearchResults.Num());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find sessions."));
	}

	if(OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->ClearOnFindSessionsCompleteDelegates(this);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online session interface is not available."));
		}	
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online subsystem is not available."));
	}
	
	TArray<FBlueprintSessionResultCustom> Results;

	if (bArg && SearchSettings.IsValid() && SearchSettings->SearchResults.Num() > 0)
	{
		for (auto& Result : SearchSettings->SearchResults)
		{
			FBlueprintSessionResultCustom BPResult;
			BPResult.OnlineResult = Result;
			Results.Add(BPResult);
		}

		OnFindSessionsSuccess.Broadcast(Results);
	}
	
	
}

void UEOS_GameInstance::JoinSession(const FBlueprintSessionResultCustom& Result)
{
	if (bIsLoggedIn )
	{
		if(OnlineSubsystem)
		{
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{
				SessionPtr->OnJoinSessionCompleteDelegates.AddUObject(this, &UEOS_GameInstance::OnJoinSessionComplete);
				SessionPtr->JoinSession(0, SessionName, Result.OnlineResult);
				UE_LOG(LogTemp, Error, TEXT("Should join session: %s"), *Result.OnlineResult.GetSessionIdStr());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online session interface is not available."));
			}	
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online subsystem is not available."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create session: User is not logged in"));
	}
}

void UEOS_GameInstance::OnJoinSessionComplete(FName Name, EOnJoinSessionCompleteResult::Type Result)
{
	if(OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			FString ConnectString;
			SessionPtr->GetResolvedConnectString(SessionName, ConnectString);
			if(!ConnectString.IsEmpty())
			{
				UE_LOG(LogTemp, Log, TEXT("Join session '%s' successful. Connecting to: %s"), *Name.ToString(), *ConnectString);
				if (APlayerController* PlayerController = GetFirstLocalPlayerController())
				{
					PlayerController->ClientTravel(ConnectString, TRAVEL_Absolute);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Join session '%s' failed: Could not resolve connect string."), *Name.ToString());
			}
			
			SessionPtr->ClearOnJoinSessionCompleteDelegates(this);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online session interface is not available."));
		}	
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online subsystem is not available."));
	}
	
}


FString UEOS_GameInstance::GetLobbyId(const FBlueprintSessionResultCustom& Result) const
{
	if (Result.OnlineResult.IsValid())
	{
		return Result.OnlineResult.GetSessionIdStr();   // EOS uses the same ID for lobby + session
	}
	return FString();
}

void UEOS_GameInstance::RequestBadgeSheet()
{
	FString URL = TEXT("https://docs.google.com/spreadsheets/d/e/2PACX-1vS2I5w4SCylTq9ZkxU9yT0_pejgYFNHMLyRa_H1FpXKT9lBY3Q7YcecIQGvbLFsnnfs7C6YWWKoMyGy/pub?output=csv");

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(URL);
	Request->SetVerb("GET");
	Request->OnProcessRequestComplete().BindUObject(this, &UEOS_GameInstance::OnResponseReceived);
	Request->ProcessRequest();
}

void UEOS_GameInstance::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		OnBadgeDataReceived.Broadcast("ERROR");
		return;
	}

	FString Result = Response->GetContentAsString();
	OnBadgeDataReceived.Broadcast(Result);
}






