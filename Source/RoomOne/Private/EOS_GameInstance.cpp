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


const FName SessionName = NAME_GameSession;

#pragma region Login and Session Management

/// @brief Constructor. Initializes the login state to false.
UEOS_GameInstance::UEOS_GameInstance(){
	bIsLoggedIn = false;
}

/// @brief Called when the game instance initializes.
/// Sets up the Online Subsystem and attempts silent login.
void UEOS_GameInstance::Init(){
	Super::Init();
	OnlineSubsystem = IOnlineSubsystem::Get();
	TrySilentLogin();
	IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
	if (Session.IsValid())
	{
		Session->OnSessionUserInviteAcceptedDelegates.AddUObject(this, &UEOS_GameInstance::OnSessionInviteAccepted);
	}
}

/// @brief Attempts to log in using EOS persistent authentication silently.
/// Will not prompt the user and is ideal for auto-login.
void UEOS_GameInstance::TrySilentLogin()
{
	if (!OnlineSubsystem){
		UE_LOG(LogTemp, Warning, TEXT("SL: no OSS"));
		return;
	}
	IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface();
	if (!Identity.IsValid()){
		UE_LOG(LogTemp, Warning, TEXT("SL: no Identity"));
		return;
	}


	FOnlineAccountCredentials Creds;
	Creds.Type  = FString("persistentauth"); // Required EOS login type
	Creds.Token = FString(); 
	Creds.Id    = FString();                    // Not used for persistent login
	
	Identity->OnLoginCompleteDelegates->AddUObject(this, &UEOS_GameInstance::OnLoginComplete);
	bIsLoggedIn = Identity->Login(0, Creds); // returns true if login is in progress
	UE_LOG(LogTemp, Log, TEXT("SL: Login() queued = %d"), bIsLoggedIn);
}

/// @brief Manually logs in the user using either developer or accountportal credentials.
/// @param dev Whether to use developer credentials (true) or EOS account portal (false).
void UEOS_GameInstance::Login(bool dev){
	// Attempt silent login first
	TrySilentLogin();

	if (OnlineSubsystem){
		// Dev login uses a hardcoded ID and token, requires the EOS_DevAuthTool to be locally set up
		if(dev){
			if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface()){
				FOnlineAccountCredentials Credentials;
				Credentials.Id = FString("127.0.0.1:8081");
				Credentials.Token = FString("CredDark");
				Credentials.Type = FString("developer");

				Identity->OnLoginCompleteDelegates->AddUObject(this, &UEOS_GameInstance::OnLoginComplete);
				Identity->Login(0, Credentials);
			}
			else{
				UE_LOG(LogTemp, Warning, TEXT("Online identity interface is not available."));
			}
		}
		// Account portal login uses the account portal credentials
		else{
			if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface()){
				FOnlineAccountCredentials Credentials;
				Credentials.Id = FString();
				Credentials.Token = FString();
				Credentials.Type = FString("accountportal");

				Identity->OnLoginCompleteDelegates->AddUObject(this, &UEOS_GameInstance::OnLoginComplete);
				Identity->Login(0, Credentials);
			}
			else{
				UE_LOG(LogTemp, Warning, TEXT("Online identity interface is not available."));
			}
		}
	}
}

/// @brief Callback for when a login attempt completes.
/// @param LocalUserNum The user index (usually 0).
/// @param bWasSuccessful Whether the login was successful.
/// @param UserId The unique ID of the user.
/// @param Error A message describing the error (if any).
void UEOS_GameInstance::OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error){
	bIsLoggedIn = bWasSuccessful;
	
	if (bWasSuccessful){
		UE_LOG(LogTemp, Log, TEXT("Login successful for user: %s"), *UserId.ToString());
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("Login failed: %s"), *Error);
	}
	
	if (OnlineSubsystem){
		if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface()){
			Identity->ClearOnLoginCompleteDelegates(0, this);
			
			playerName = Identity->GetPlayerNickname(0);
			TSharedPtr<const FUniqueNetId> NetId = Identity->GetUniquePlayerId(0);
			
			if (NetId.IsValid()){
				userId = NetId->ToString();
				UE_LOG(LogTemp, Log, TEXT("Got user ID: %s"), *userId);
			}
			else{
				UE_LOG(LogTemp, Error, TEXT("Failed to get Unique Player ID"));
			}
			
			UE_LOG(LogTemp, Log, TEXT("Fetched DisplayName: %s"), *playerName);
		}
		else{
			UE_LOG(LogTemp, Error, TEXT("Online identity interface is not available."));
		}
	}
}

/// @brief Logs out the current user and clears the login flag.
void UEOS_GameInstance::ForceLogout(){
	
	if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface()){
		Identity->Logout(0);
	}

	bIsLoggedIn = false;
}


/// @brief Creates a multiplayer session with EOS settings if logged in.
void UEOS_GameInstance::CreateSession(){
	if (bIsLoggedIn ){
		if(OnlineSubsystem){
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface()){
				FOnlineSessionSettings SessionSettings;
				SessionSettings.bIsDedicated = false;
				SessionSettings.bShouldAdvertise = true;
				SessionSettings.bIsLANMatch = false;
				SessionSettings.NumPublicConnections = 15;
				SessionSettings.bAllowJoinInProgress = true;
				SessionSettings.bAllowJoinViaPresence = true;
				SessionSettings.bUsesPresence = true;
				SessionSettings.bUseLobbiesIfAvailable = true;
				SessionSettings.bAllowInvites = true;
				

				SessionSettings.Set(SEARCH_KEYWORDS, FString("DarkCred"), EOnlineDataAdvertisementType::ViaOnlineService);

				SessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UEOS_GameInstance::OnCreateSessionComplete);
				SessionPtr->CreateSession(0, SessionName, SessionSettings);

				OnPrintConsoleMessage("Attempting to create session");
			}
			else{
				UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online session interface is not available."));
			}
		}
		else{
			UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online subsystem is not available."));
		}
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create session: User is not logged in"));
	}
}

/// @brief Callback when session creation completes.
/// @param Name The name of the session.
/// @param bArg True if successful, false otherwise.
void UEOS_GameInstance::OnCreateSessionComplete(FName Name, bool bArg){
	if (bArg){
		UE_LOG(LogTemp, Log, TEXT("Session '%s' created successfully."), *Name.ToString());
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface()){
			if (FNamedOnlineSession* Named = SessionPtr->GetNamedSession(Name)){
				CurrentLobbyId = Named->GetSessionIdStr();           // cache it for anyone who asks
				OnPrintConsoleMessage(FString::Printf(TEXT("Created session with ID: %s"), *CurrentLobbyId));
				UE_LOG(LogTemp, Log, TEXT("Created lobby ID: %s"), *CurrentLobbyId);
			}
		}
	}
	else{
		OnPrintConsoleMessage("Failed to create session.");
		UE_LOG(LogTemp, Warning, TEXT("Failed to create session '%s'."), *Name.ToString());
	}

	if (OnlineSubsystem){
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface()){
			SessionPtr->ClearOnCreateSessionCompleteDelegates(this);
		}
		else{
			UE_LOG(LogTemp, Warning, TEXT("Online session interface is not available."));
		}
	}
}

/// @brief Destroys the current session if one exists.
void UEOS_GameInstance::DestroySession(){
	if (bIsLoggedIn ){
		if(OnlineSubsystem){
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface()){
				SessionPtr->OnDestroySessionCompleteDelegates.AddUObject(this, &UEOS_GameInstance::OnDestroySessionComplete);
				SessionPtr->DestroySession(SessionName);
			}
			else{
				UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online session interface is not available."));
			}
		}
		else{
			UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online subsystem is not available."));
		}
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create session: User is not logged in"));
	}
}

/// @brief Callback when session destruction completes.
/// @param Name Name of the destroyed session.
/// @param bArg True if successful.
void UEOS_GameInstance::OnDestroySessionComplete(FName Name, bool bArg){
	if(bArg){
		UE_LOG(LogTemp, Log, TEXT("Session '%s' destroyed successfully."), *Name.ToString());
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("Failed to destroy session '%s'."), *Name.ToString());
	}
	
	if(OnlineSubsystem){
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface()){
			SessionPtr->ClearOnDestroySessionCompleteDelegates(this);
		}
		else{
			UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online session interface is not available."));
		}
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online subsystem is not available."));
	}

	
}

/// @brief Destroys the session on the client side if it exists and we are not the host.
void UEOS_GameInstance::DestroySessionOnClient() {
	if (!OnlineSubsystem || !bIsLoggedIn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot destroy session: Not logged in or OSS missing."));
		return;
	}

	IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
	if (!Session.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot destroy session: Session interface invalid."));
		return;
	}

	FNamedOnlineSession* ExistingSession = Session->GetNamedSession(SessionName);
	if (!ExistingSession)
	{
		UE_LOG(LogTemp, Log, TEXT("No existing session to destroy."));
		return;
	}
	
	if (!ExistingSession->bHosting)
	{
		UE_LOG(LogTemp, Log, TEXT("Destroying client session to clean up lobby state."));
		Session->OnDestroySessionCompleteDelegates.AddUObject(this, &UEOS_GameInstance::OnDestroySessionComplete);
		Session->DestroySession(SessionName);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Skipping destroy — we are the host."));
	}
}

/// @brief Searches for available sessions using EOS search parameters.
void UEOS_GameInstance::FindSessions(){
	if (bIsLoggedIn ){
		if(OnlineSubsystem){
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface()){
				SearchSettings = MakeShareable(new FOnlineSessionSearch());
				SearchSettings->MaxSearchResults = 5000;
				SearchSettings->QuerySettings.Set(SEARCH_KEYWORDS, FString("DarkCred"), EOnlineComparisonOp::Equals);
				SearchSettings->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
				SessionPtr->OnFindSessionsCompleteDelegates.AddUObject(this, &UEOS_GameInstance::OnFindSessionsComplete);
				SessionPtr->FindSessions(0, SearchSettings.ToSharedRef());
				
			}
			else{
				UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online session interface is not available."));
			}	
		}
		else{
			UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online subsystem is not available."));
		}
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create session: User is not logged in"));
	}	
}

/// @brief Callback for when session search completes.
/// @param bArg True if sessions were found successfully.
void UEOS_GameInstance::OnFindSessionsComplete(bool bArg){
	if(bArg){
		UE_LOG(LogTemp, Log, TEXT("Find sessions completed successfully."));
		UE_LOG(LogTemp, Log, TEXT("Found %d sessions."), SearchSettings->SearchResults.Num());
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find sessions."));
	}

	if(OnlineSubsystem){
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface()){
			SessionPtr->ClearOnFindSessionsCompleteDelegates(this);
		}
		else{
			UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online session interface is not available."));
		}	
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online subsystem is not available."));
	}
	
	TArray<FBlueprintSessionResultCustom> Results;

	if (bArg && SearchSettings.IsValid() && SearchSettings->SearchResults.Num() > 0){
		for (auto& Result : SearchSettings->SearchResults){
			FBlueprintSessionResultCustom BPResult;
			BPResult.OnlineResult = Result;
			Results.Add(BPResult);
		}

		OnFindSessionsSuccess.Broadcast(Results);
	}
}

void UEOS_GameInstance::OnPrintConsoleMessage_Implementation(const FString& text) {
	UE_LOG(LogTemp, Log, TEXT("%s"), *text);
}

void UEOS_GameInstance::OnPostJoinSession_Implementation() {
}

/// @brief Attempts to join a selected session.
/// @param Result The session result to join.
void UEOS_GameInstance::JoinSession(const FBlueprintSessionResultCustom& Result){
	if (Result.OnlineResult.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Result is valid. SessionId: %s"), *Result.OnlineResult.GetSessionIdStr());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Result.OnlineResult is NOT valid"));
	}
	
	if (OnlineSubsystem){
    	if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface()){
    		OnPrintConsoleMessage("Attempting to join session: " + Result.OnlineResult.GetSessionIdStr()); 
    		if (SessionPtr->GetNamedSession(SessionName)){
    			UE_LOG(LogTemp, Warning, TEXT("Destroying previous session '%s' before rejoining."), *SessionName.ToString());
    			SessionPtr->DestroySession(SessionName);
    		}
    	}
    }


	// Patch search result flags (Steam workaround)
	FOnlineSessionSearchResult* SearchResultPtr = const_cast<FOnlineSessionSearchResult*>(&Result.OnlineResult);
	SearchResultPtr->Session.SessionSettings.bUsesPresence = true;
	SearchResultPtr->Session.SessionSettings.bUseLobbiesIfAvailable = true;
	
	if (bIsLoggedIn ){
		if(OnlineSubsystem){
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface()){
				SessionPtr->OnJoinSessionCompleteDelegates.AddUObject(this, &UEOS_GameInstance::OnJoinSessionComplete);
				SessionPtr->JoinSession(0, SessionName, *SearchResultPtr);
				OnPrintConsoleMessage("Session Found, Connecting...");
				UE_LOG(LogTemp, Error, TEXT("Should join session: %s"), *Result.OnlineResult.GetSessionIdStr());
			}
			else{
				OnPrintConsoleMessage("Error: Online session interface is not available.");
				UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online session interface is not available."));
			}	
		}
		else{
			OnPrintConsoleMessage("Error: Online subsystem is not available.");
			UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online subsystem is not available."));
		}
	}
	else{
		OnPrintConsoleMessage("Error: User is not logged in");
		UE_LOG(LogTemp, Warning, TEXT("Cannot create session: User is not logged in"));
	}
}

/// @brief Callback for when a session join attempt completes.
/// @param Name Name of the session.
/// @param Result Join session result enum.
void UEOS_GameInstance::OnJoinSessionComplete(FName Name, EOnJoinSessionCompleteResult::Type Result){

	FString ConnectString2;
	bool bGotConnect = OnlineSubsystem->GetSessionInterface()->GetResolvedConnectString(SessionName, ConnectString2);

	if (bGotConnect){
		UE_LOG(LogTemp, Log, TEXT("Join session '%s' successful. Connecting to: %s"), *Name.ToString(), *ConnectString2);

		OnPostJoinSession();
		
		if (APlayerController* PlayerController = GetFirstLocalPlayerController()){
			PlayerController->ClientTravel(ConnectString2, TRAVEL_Absolute);
		}
	}
	else{
		UE_LOG(LogTemp, Error, TEXT("❌ Failed to resolve connect string for session: '%s'"), *Name.ToString());
		if (FNamedOnlineSession* Session = OnlineSubsystem->GetSessionInterface()->GetNamedSession(Name)){
			UE_LOG(LogTemp, Warning, TEXT("Session found: %s"), *Session->SessionName.ToString());
			UE_LOG(LogTemp, Warning, TEXT("OwningUserId: %s"), *Session->OwningUserId->ToString());
			UE_LOG(LogTemp, Warning, TEXT("SessionId: %s"), *Session->GetSessionIdStr());
			UE_LOG(LogTemp, Warning, TEXT("NumOpenPublicConnections: %d"), Session->NumOpenPublicConnections);
			UE_LOG(LogTemp, Warning, TEXT("SessionSettings: bIsLANMatch=%d, bUsesPresence=%d, bUseLobbiesIfAvailable=%d"),
				Session->SessionSettings.bIsLANMatch,
				Session->SessionSettings.bUsesPresence,
				Session->SessionSettings.bUseLobbiesIfAvailable);
		}
		else{
			UE_LOG(LogTemp, Error, TEXT("No session object found with name: %s"), *Name.ToString());
		}
	}
	
	if(OnlineSubsystem){
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface()){
			
			FString ConnectString;
			
			
			if(!ConnectString.IsEmpty()){
				UE_LOG(LogTemp, Log, TEXT("Join session '%s' successful. Connecting to: %s"), *Name.ToString(), *ConnectString);
				if (APlayerController* PlayerController = GetFirstLocalPlayerController()){
					PlayerController->ClientTravel(ConnectString, TRAVEL_Absolute);
				}
			}
			else{
				UE_LOG(LogTemp, Warning, TEXT("Join session '%s' failed: Could not resolve connect string."), *Name.ToString());
			}
			
			SessionPtr->ClearOnJoinSessionCompleteDelegates(this);
		}
		else{
			UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online session interface is not available."));
		}	
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create session: Online subsystem is not available."));
	}
}

/// @brief Gets the lobby/session ID from a session result.
/// @param Result The session result.
/// @return The session's unique ID string.
FString UEOS_GameInstance::GetLobbyId(const FBlueprintSessionResultCustom& Result) const{
	if (Result.OnlineResult.IsValid()){
		return Result.OnlineResult.GetSessionIdStr();   // EOS uses the same ID for lobby + session
	}
	return FString();
}


void UEOS_GameInstance::OnSessionInviteAccepted(
	const bool bWasSuccessful,
	int32 LocalUserNum,
	TSharedPtr<const FUniqueNetId> InvitingPlayer,
	const FOnlineSessionSearchResult& SessionToJoin)
{
	UE_LOG(LogTemp, Log, TEXT("Smth happened%s"), *InvitingPlayer->ToString());
	if (bWasSuccessful && SessionToJoin.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Invite accepted from %s"), *InvitingPlayer->ToString());

		// Optional: Destroy old session before joining
		IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
		if (Session->GetNamedSession(SessionName))
		{
			Session->DestroySession(SessionName);
		}

		// Join the session
		JoinSession(FBlueprintSessionResultCustom{SessionToJoin});
	}
}



#pragma endregion

#pragma region Badge Sheets

/// @brief Sends an HTTP GET request to fetch the public badge sheet CSV.
/// The response will be handled asynchronously by OnResponseReceived().
void UEOS_GameInstance::RequestBadgeSheet(){
	const FString URL = TEXT("https://docs.google.com/spreadsheets/d/e/2PACX-1vS2I5w4SCylTq9ZkxU9yT0_pejgYFNHMLyRa_H1FpXKT9lBY3Q7YcecIQGvbLFsnnfs7C6YWWKoMyGy/pub?output=csv");

	// Create the HTTP request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(URL);
	Request->SetVerb("GET");
	
	// Bind completion callback and send the request
	Request->OnProcessRequestComplete().BindUObject(this, &UEOS_GameInstance::OnResponseReceived);
	Request->ProcessRequest();
}

/// @brief Callback for when the badge sheet HTTP request completes.
/// @param Request The original HTTP request object.
/// @param Response The HTTP response from the server.
/// @param bWasSuccessful Whether the request was completed successfully.
void UEOS_GameInstance::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) const {
	if (!bWasSuccessful || !Response.IsValid()){
		OnBadgeDataReceived.Broadcast("ERROR"); // Notify listeners of failure
		return;
	}

	FString Result = Response->GetContentAsString();
	OnBadgeDataReceived.Broadcast(Result); // Send data to Blueprint or C++ listeners
}

#pragma endregion

#pragma region Game Codes

/// @brief Sends an HTTP GET request to fetch the public badge sheet CSV.
/// The response will be handled asynchronously by OnResponseReceived().
void UEOS_GameInstance::RequestGameCodes(){
	const FString URL = TEXT("https://docs.google.com/spreadsheets/d/e/2PACX-1vQ2RnuafJBwfCxdC5HjFVF7ztgeafZlc_uZjZ88IQk28I-xU_Qr-GB4SHxmCzQsDziEJd8O7Z0IQWKy/pub?output=csv");

	// Create the HTTP request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(URL);
	Request->SetVerb("GET");
	
	// Bind completion callback and send the request
	Request->OnProcessRequestComplete().BindUObject(this, &UEOS_GameInstance::OnGameCodeResponseReceived);
	Request->ProcessRequest();
}

/// @brief Callback for when the badge sheet HTTP request completes.
/// @param Request The original HTTP request object.
/// @param Response The HTTP response from the server.
/// @param bWasSuccessful Whether the request was completed successfully.
void UEOS_GameInstance::OnGameCodeResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) const {
	if (!bWasSuccessful || !Response.IsValid()){
		OnGameDataReceived.Broadcast("ERROR"); // Notify listeners of failure
		return;
	}

	FString Result = Response->GetContentAsString();
	OnGameDataReceived.Broadcast(Result); // Send data to Blueprint or C++ listeners
}



/// @brief Adds a game code to the public Google Sheet.
/// @param Code The code to add.
/// @param LobbyId The related lobby ID.
void UEOS_GameInstance::AddGameCode(const FString& Code, const FString& LobbyId)
{
	const FString EncodedCode = FGenericPlatformHttp::UrlEncode(Code);
	const FString EncodedLobby = FGenericPlatformHttp::UrlEncode(LobbyId);
	const FString URL = FString::Printf(
		TEXT("https://script.google.com/macros/s/AKfycbxUPAEuiOw9eN4W4kVklZt8X5dt2np-YD154VAbZRS6Qqj18-VTHVEQzo3ls_BkqeQu/exec?action=add&code=%s&lobbyID=%s"),
		*EncodedCode, *EncodedLobby
	);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(URL);
	Request->SetVerb("GET");
	Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Req, FHttpResponsePtr Res, bool bSuccess) {
		UE_LOG(LogTemp, Log, TEXT("AddGameCode: %s"), bSuccess ? *Res->GetContentAsString() : TEXT("Failed"));
	});
	Request->ProcessRequest();
}

/// @brief Removes a game code from the public Google Sheet.
/// @param Code The code to remove.
void UEOS_GameInstance::RemoveGameCode(const FString& Code)
{
	const FString EncodedCode = FGenericPlatformHttp::UrlEncode(Code);
	const FString URL = FString::Printf(
		TEXT("https://script.google.com/macros/s/AKfycbxUPAEuiOw9eN4W4kVklZt8X5dt2np-YD154VAbZRS6Qqj18-VTHVEQzo3ls_BkqeQu/exec?action=remove&code=%s"),
		*EncodedCode
	);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(URL);
	Request->SetVerb("GET");
	Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Req, FHttpResponsePtr Res, bool bSuccess) {
		UE_LOG(LogTemp, Log, TEXT("RemoveGameCode: %s"), bSuccess ? *Res->GetContentAsString() : TEXT("Failed"));
	});
	Request->ProcessRequest();
}

#pragma endregion



