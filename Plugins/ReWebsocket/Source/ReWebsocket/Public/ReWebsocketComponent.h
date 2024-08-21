// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WebSocketsModule.h"
#include "IWebSocket.h"
#include "ReWebsocketComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REWEBSOCKET_API UReWebsocketComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UReWebsocketComponent();
	~UReWebsocketComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReWebsocket Properties")
		bool bPrintLog = false;


	UFUNCTION(BlueprintCallable, Category = "ReWebsocket Functions")
		void Connect(const FString& Url, const TArray<FString>& Protocols, const TMap<FString, FString>& UpgradeHeaders);
	UFUNCTION(BlueprintCallable, Category = "ReWebsocket Functions")
		void Close(int32 Code = 1000, const FString& Reason = "");
	UFUNCTION(BlueprintPure, Category = "ReWebsocket Functions")
		bool IsConnected();
	UFUNCTION(BlueprintCallable, Category = "ReWebsocket Functions")
		void Send(const FString& Data);
	UFUNCTION(BlueprintCallable, Category = "ReWebsocket Functions")
		void SendBinary(const TArray<uint8>& RawData);


	/**
	 * Delegate called when a web socket connection has been established successfully.
	 *
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReWebSocketConnectedEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReWebSocketConnectionErrorEvent, const FString&, ErrorMessage);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReWebSocketClosedEvent, int32, StatusCode, const FString&, Reason, bool, bWasClean);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReWebSocketMessageEvent, const FString&, MessageString);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReWebSocketRawMessageEvent, const TArray<uint8>&, RawMessage);

	UPROPERTY(BlueprintAssignable, Category = "ReWebsocket Events")
		FReWebSocketConnectedEvent OnConnected;
	UPROPERTY(BlueprintAssignable, Category = "ReWebsocket Events")
		FReWebSocketConnectionErrorEvent OnConnectionError;
	UPROPERTY(BlueprintAssignable, Category = "ReWebsocket Events")
		FReWebSocketClosedEvent OnClosed;
	UPROPERTY(BlueprintAssignable, Category = "ReWebsocket Events")
		FReWebSocketMessageEvent OnMessage;
	// UPROPERTY(BlueprintAssignable, Category = "ReWebsocket Events")
	// 	FReWebSocketRawMessageEvent OnRawMessage;
private:
	void ClearCallbacks();
	void SetupCallbacks();

	TSharedPtr<IWebSocket> m_WebSocket;
	//TArray<uint8> m_RawMessage;
};
