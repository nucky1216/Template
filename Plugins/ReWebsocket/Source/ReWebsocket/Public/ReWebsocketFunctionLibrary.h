// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReWebsocketFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class REWEBSOCKET_API UReWebsocketFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "ReWebsocket Funtion Library")
		static void SliceRawData (TArray<uint8>& SlicedData, const TArray<uint8>& RawData, int32 BeginIndex, int32 EndIndex);
	UFUNCTION(BlueprintCallable, Category = "ReWebsocket Funtion Library")
		static void RawDataToString(FString& StringData, const TArray<uint8>& RawData, int32 BeginIndex, int32 EndIndex);

private:
	static void WarpRawDataIndex(int32& Index, int32 DataLength);
};
