#include "ChatGameManager.h"
#include "ChatPlayerController.h"
#include "ChatGameMode.h"

void UChatGameManager::Initialize(AChatGameMode* InGameMode)
{
    if (InGameMode)
    {
        GameMode = InGameMode;
        World = InGameMode->GetWorld();
    }
}

void UChatGameManager::GenerateRandomNumber()
{
    RandomNumber.Empty();

    // 1~9의 중복 없는 3자리 숫자 생성 로직
    TArray<int32> AvailableDigits = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (int i = 0; i < 3; i++)
    {
        int32 Index = FMath::RandRange(0, AvailableDigits.Num() - 1);
        RandomNumber.Add(AvailableDigits[Index]);

        UE_LOG(LogTemp, Warning, TEXT("Random Number Digit: %d"), AvailableDigits[Index]);

        AvailableDigits.RemoveAt(Index);
    }
}

void UChatGameManager::ProcessChatCommand(const FString& Command, AChatPlayerController* SenderPlayerController)
{
    FString HostName;
    FString Message;

    if (Command.Split(TEXT(": "), &HostName, &Message))  // ": " 이후 부분을 메시지로 분리
    {
        // 메시지가 3자리 숫자인지 확인
        if (Message.Len() == 3 && Message.IsNumeric())
        {
            int32 Guess = FCString::Atoi(*Message);

            // 숫자 유효성 검사
            if (IsValidGuess(Guess))
            {
                FString Result = JudgeGuess(Guess, SenderPlayerController);

                // 게임 결과를 모든 플레이어에게 전송
                BroadcastToPlayers(Command + " -> " + Result);

                // 만약 한 명이 3 스트라이크를 맞췄다면 게임 종료 처리
                if (Result == TEXT("Winner"))
                {
                    DisplayResultUI(true);
                    return; // 승리한 후 더 이상 진행하지 않도록
                }
            }
            else
            {
                BroadcastToPlayers(Command + " -> " + TEXT("InValid, OUT"));
            }
        }
        else
        {
            BroadcastToPlayers(Command + " -> " + TEXT("Len Error, OUT"));
        }
    }
    else
    {
        BroadcastToPlayers(Command + " -> " + TEXT("Split Error, OUT"));
    }

    if (AreAllPlayersAttemptsZero())
    {
        DisplayResultUI(false);
    }
}

FString UChatGameManager::JudgeGuess(int32 Guess, AChatPlayerController* SenderPlayerController)
{
    // 숫자와 비교하여 스트라이크/볼/아웃 계산
    TArray<int32> GuessDigits = { Guess / 100, (Guess / 10) % 10, Guess % 10 };
    int32 StrikeCount = 0, BallCount = 0;

    for (int i = 0; i < 3; i++)
    {
        if (GuessDigits[i] == RandomNumber[i])
        {
            StrikeCount++;
        }
        else if (RandomNumber.Contains(GuessDigits[i]))
        {
            BallCount++;
        }
    }

    // 스트라이크와 볼 결과가 모두 0이면 "OUT"을 반환
    if (StrikeCount == 0 && BallCount == 0)
    {
        return TEXT("OUT");
    }
    else if (StrikeCount == 3)
    {
        SenderPlayerController->bIsWinner = true;
        return TEXT("Winner");
    }

    // 스트라이크와 볼 결과 반환
    return FString::Printf(TEXT("S: %d, B: %d"), StrikeCount, BallCount);
}

bool UChatGameManager::IsValidGuess(int32 Guess)
{
    // 3자리 숫자인지, 중복되지 않은 숫자인지 검사
    TArray<int32> Digits = { Guess / 100, (Guess / 10) % 10, Guess % 10 };
    return Digits[0] != Digits[1] && Digits[0] != Digits[2] && Digits[1] != Digits[2];
}

void UChatGameManager::DisplayResultUI(bool bIsWinner)
{
    if (!World) return;

    for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
    {
        AChatPlayerController* ChatPC = Cast<AChatPlayerController>(*It);

        if (ChatPC)
        {
            // 승자가 존재할경우
            if (bIsWinner)
            {
                if (ChatPC->bIsWinner)
                {
                    ChatPC->DisplayGameOverUI("You Win !");
                }
                else
                {
                    ChatPC->DisplayGameOverUI("You Lose !");
                }
            }
            else
            {
                ChatPC->DisplayGameOverUI("You Draw !");
            }
        }
    }
}

bool UChatGameManager::AreAllPlayersAttemptsZero()
{
    if (World)
    {
        // 모든 플레이어 컨트롤러를 순회
        for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
        {
            AChatPlayerController* ChatPC = Cast<AChatPlayerController>(*It);
            if (ChatPC)
            {
                if (ChatPC->PlayerAttempts > 0)
                {
                    return false;
                }
            }
        }

        // 모든 플레이어의 attempts가 0일 경우 true 반환
        return true;
    }
    else
    {
        return false;
    }
}

void UChatGameManager::BroadcastToPlayers(const FString& Message)
{
    if (!World) return;

    for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
    {
        AChatPlayerController* ChatPC = Cast<AChatPlayerController>(*It);
        if (ChatPC)
        {
            ChatPC->ClientReceiveChatMessage(Message);
        }
    }
}
