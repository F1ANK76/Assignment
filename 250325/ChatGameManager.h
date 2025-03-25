#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ChatGameManager.generated.h"

class AChatGameMode;
class AChatPlayerController;

UCLASS()
class SPARTAPROJECT_API UChatGameManager : public UObject
{
    GENERATED_BODY()

public:

    // 3자리 숫자 생성 함수
    void GenerateRandomNumber();

    void Initialize(AChatGameMode* InGameMode);

    // 채팅 명령어 처리 함수
    void ProcessChatCommand(const FString& Command, AChatPlayerController* SenderPlayerController);

    // 숫자 비교 후 스트라이크/볼 계산하는 함수
    FString JudgeGuess(int32 Guess, AChatPlayerController* SenderPlayerController);

    // 유효한 숫자인지 검사하는 함수
    bool IsValidGuess(int32 Guess);

    void DisplayResultUI(bool bIsWinner);

    // 모든 플레이어의 시도 횟수가 0인지 확인하는 함수
    bool AreAllPlayersAttemptsZero();

    // 게임 결과를 모든 플레이어에게 전송하는 함수
    void BroadcastToPlayers(const FString& Message);

    AChatGameMode* GameMode;

    // GameMode의 World를 사용하기 위한 변수
    UWorld* World;

    // 서버에서 생성한 난수 (1~9의 중복 없는 3자리 숫자)
    TArray<int32> RandomNumber;
};

