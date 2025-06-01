// Fill out your copyright notice in the Description page of Project Settings.


#include "EOS_GameInstance.h"

#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Online/OnlineSessionNames.h"

const FName SessionName = FName("Test_Session");

UEOS_GameInstance::UEOS_GameInstance()
{
	bIsLoggedIn = false;
}

void UEOS_GameInstance::Init()
{
	Super::Init();
	
	OnlineSubsystem = IOnlineSubsystem::Get();
}


void UEOS_GameInstance::Login(bool dev)
{
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
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Online identity interface is not available."));
		}
	}
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









