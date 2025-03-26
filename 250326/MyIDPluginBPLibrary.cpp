// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyIDPluginBPLibrary.h"
#include "MyIDPlugin.h"

FString UMyIDPluginBPLibrary::UserName = TEXT("");  // 정적 변수 초기화

UMyIDPluginBPLibrary::UMyIDPluginBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UMyIDPluginBPLibrary::MyIDPluginSampleFunction(float Param)
{
	return -1;
}

void UMyIDPluginBPLibrary::SetUserName(const FString& NewName)
{
    UserName = NewName;
    UE_LOG(LogTemp, Log, TEXT("UserName set to: %s"), *UserName);
}

FString UMyIDPluginBPLibrary::GetUserName()
{
    return UserName;
}
