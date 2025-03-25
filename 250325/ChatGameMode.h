// ChatGameMode.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChatGameMode.generated.h"

class AChatPlayerController;
class UChatGameManager;

UCLASS()
class SPARTAPROJECT_API AChatGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
    UPROPERTY()
    UChatGameManager* ChatGameManager;

    // 게임이 시작될 때 호출되는 함수
    virtual void StartPlay() override;

    // 채팅 명령어 처리 함수
    void ProcessChatCommand(const FString& Command, AChatPlayerController* SenderPlayerController);
};
