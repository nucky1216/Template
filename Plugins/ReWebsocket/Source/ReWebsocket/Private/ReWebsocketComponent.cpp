// Fill out your copyright notice in the Description page of Project Settings.


#include "ReWebsocketComponent.h"
#include "ReWebsocket.h"

// Sets default values for this component's properties
UReWebsocketComponent::UReWebsocketComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// Nancy is so cute
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


UReWebsocketComponent::~UReWebsocketComponent()
{
	
}

// Called when the game starts
void UReWebsocketComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UReWebsocketComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ClearCallbacks();
	if (IsConnected()) {
		Close(1000, FString());
	}
	m_WebSocket.Reset();
}

// Called every frame
void UReWebsocketComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UReWebsocketComponent::Connect(const FString & Url, const TArray<FString>& Protocols, const TMap<FString, FString>& UpgradeHeaders)
{
	
	if (IsConnected()) {
		ClearCallbacks();
		Close(1000, FString());
		m_WebSocket.Reset();
	}
	m_WebSocket = FWebSocketsModule::Get().CreateWebSocket(Url, Protocols, UpgradeHeaders);
	SetupCallbacks();
	m_WebSocket->Connect();
	
}

void UReWebsocketComponent::Close(int32 Code, const FString & Reason)
{
	if (m_WebSocket) {
		m_WebSocket->Close(Code, Reason);
	}
}


bool UReWebsocketComponent::IsConnected()
{
	if (m_WebSocket) {
		return m_WebSocket->IsConnected();
	}
	return false;
}

void UReWebsocketComponent::Send(const FString& Data)
{
	if (m_WebSocket) {
		m_WebSocket->Send(Data);
	}
}

void UReWebsocketComponent::SendBinary(const TArray<uint8>& RawData)
{
	if (m_WebSocket) {
		m_WebSocket->Send(RawData.GetData(), RawData.Num(), true);
	}
}

void UReWebsocketComponent::ClearCallbacks()
{
	if (m_WebSocket) {
		m_WebSocket->OnConnected().Clear();
		m_WebSocket->OnConnectionError().Clear();
		m_WebSocket->OnClosed().Clear();
		m_WebSocket->OnMessage().Clear();
		m_WebSocket->OnRawMessage().Clear();
	}
	
}

void UReWebsocketComponent::SetupCallbacks()
{
	if (m_WebSocket) {
		m_WebSocket->OnConnected().AddLambda([this]()
			{
				this->OnConnected.Broadcast(); 
				if(bPrintLog) UE_LOG(ReWebsocketLog, Log, TEXT("Websocket client connected."));
			});
		m_WebSocket->OnConnectionError().AddLambda([this](const FString& ErrorMessage)
			{
				this->OnConnectionError.Broadcast(ErrorMessage);
				if (bPrintLog) UE_LOG(ReWebsocketLog, Log, TEXT("Websocket get error : %s"), *ErrorMessage);
			});
		m_WebSocket->OnClosed().AddLambda([this](int32 StatusCode, const FString& Reason, bool bWasClean)
			{
				this->OnClosed.Broadcast(StatusCode, Reason, bWasClean); 
				if (bPrintLog) UE_LOG(ReWebsocketLog, Log, TEXT("Websocket close with reason : %s"), *Reason);
			});
		m_WebSocket->OnMessage().AddLambda([this](const FString& MessageString)
			{
				this->OnMessage.Broadcast(MessageString);
			});
		// m_WebSocket->OnRawMessage().AddLambda([this](const void* Data, SIZE_T Size, SIZE_T BytesRemaining)
		// 	{
		// 		if (this->m_RawMessage.Num() == 0) {
		// 			this->m_RawMessage.SetNumZeroed(Size + BytesRemaining);
		// 		}
		// 		SIZE_T offset = this->m_RawMessage.Num() - Size - BytesRemaining;
		// 		FMemory::Memcpy(this->m_RawMessage.GetData() + offset, Data, Size);
		// 		if (BytesRemaining == 0) {
		// 			this->OnRawMessage.Broadcast(this->m_RawMessage);
		// 			this->m_RawMessage.Empty();
		// 		}
		// 	});
	}
}

