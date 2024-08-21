// Fill out your copyright notice in the Description page of Project Settings.


#include "ReWebsocketFunctionLibrary.h"

void UReWebsocketFunctionLibrary::SliceRawData(TArray<uint8>& SlicedData, const TArray<uint8>& RawData, int32 BeginIndex, int32 EndIndex)
{
	WarpRawDataIndex(BeginIndex, RawData.Num());
	WarpRawDataIndex(EndIndex, RawData.Num());
	int32 DataLength = EndIndex - BeginIndex + 1;
	if (DataLength < 0) {
		return;
	}
	SlicedData.SetNumZeroed(DataLength);
	FMemory::Memcpy(SlicedData.GetData(), RawData.GetData() + BeginIndex, DataLength);
}

void UReWebsocketFunctionLibrary::RawDataToString(FString& StringData, const TArray<uint8>& RawData, int32 BeginIndex, int32 EndIndex)
{
	TArray<uint8> SlicedData;
	SliceRawData(SlicedData, RawData, BeginIndex, EndIndex);
	SlicedData.Add('\0');
	StringData = reinterpret_cast<const char*>(SlicedData.GetData());
}

void UReWebsocketFunctionLibrary::WarpRawDataIndex(int32& Index, int32 DataLength)
{
	if (Index >= DataLength)
	{
		Index = DataLength - 1;
	}
	else if(Index < 0)
	{
		Index += DataLength;
		if (Index < 0) {
			Index = 0;
		}
	}
}
