// ChatGameMode.cpp

#include "ChatGameMode.h"
#include "ChatGameManager.h"

void AChatGameMode::StartPlay()
{
    Super::StartPlay();

    ChatGameManager = NewObject<UChatGameManager>();
    ChatGameManager->Initialize(this);

    ChatGameManager->GenerateRandomNumber();

    // 게임 리스타트시 딜레이없는 화면 전환 옵션
    bUseSeamlessTravel = true;
}

void AChatGameMode::ProcessChatCommand(const FString& Command, AChatPlayerController* SenderPlayerController)
{
    ChatGameManager->ProcessChatCommand(Command, SenderPlayerController);
}
