// ChatPlayerController.cpp

#include "ChatPlayerController.h"
#include "Chatting.h"
#include "ChatGameMode.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

AChatPlayerController::AChatPlayerController()
{
    PlayerAttempts = 3;
    bIsWinner = false;
}

void AChatPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // 로컬 플레이어인 경우에만 UI를 추가합니다.
    if (IsLocalPlayerController())
    {
        ShowChatWidget();
    }
}

void AChatPlayerController::ShowChatWidget()
{
    if (WBP_Chatting)
    {
        // WBP_Chatting을 사용하여 위젯을 생성
        ChatWidget = CreateWidget<UChatting>(this, WBP_Chatting);

        if (ChatWidget)
        {
            ChatWidget->AddToViewport();
        }
    }
}

// 서버로 채팅 메시지를 전송하는 함수
bool AChatPlayerController::ServerSendChatMessage_Validate(const FString& Message)
{
    // 메시지가 비어있지 않으면 유효하다고 판단
    return !Message.IsEmpty();
}

void AChatPlayerController::ServerSendChatMessage_Implementation(const FString& Message)
{
    // 서버가 게임 모드에 명령어 전달
    AChatGameMode* GameMode = Cast<AChatGameMode>(GetWorld()->GetAuthGameMode());

    if (GameMode)
    {
        GameMode->ProcessChatCommand(Message, this);
    }
}

// 클라이언트에서 메시지를 수신하여 처리
void AChatPlayerController::ClientReceiveChatMessage_Implementation(const FString& Message)
{
    if (ChatWidget)
    {
        ChatWidget->AddChatMessage(Message);
    }
}

void AChatPlayerController::DisplayGameOverUI_Implementation(const FString& Message)
{
    // 로컬 플레이어에 대해서만 UI를 표시
    if (IsLocalPlayerController() && GameOverUIClass)
    {
        GameOverUIWidget = CreateWidget<UUserWidget>(this, GameOverUIClass);

        if (GameOverUIWidget)
        {
            // 텍스트 블록을 찾기 (위젯에 텍스트 블록이 바인딩 되어 있다고 가정)
            UTextBlock* ResultTextBlock = Cast<UTextBlock>(GameOverUIWidget->GetWidgetFromName(TEXT("GameOverText")));

            if (ResultTextBlock)
            {
                // 메시지를 설정
                ResultTextBlock->SetText(FText::FromString(Message));
            }

            UButton* RestartButton = Cast<UButton>(GameOverUIWidget->GetWidgetFromName(TEXT("ReStartBtn")));
            if (RestartButton)
            {
                // 버튼 클릭 시 이벤트 바인딩
                RestartButton->OnClicked.AddDynamic(this, &AChatPlayerController::OnRestartGame);
            }

            // 게임 종료 버튼 찾기
            UButton* ExitButton = Cast<UButton>(GameOverUIWidget->GetWidgetFromName(TEXT("EndBtn")));
            if (ExitButton)
            {
                // 버튼 클릭 시 이벤트 바인딩
                ExitButton->OnClicked.AddDynamic(this, &AChatPlayerController::OnExitGame);
            }

            GameOverUIWidget->AddToViewport();
        }
    }
}

void AChatPlayerController::ServerDecreasePlayerAttempts_Implementation()
{
    if (PlayerAttempts > 0)
    {
        PlayerAttempts--;

        // 시도 횟수가 변경된 후, 모든 클라이언트에 이를 업데이트
        MulticastUpdatePlayerAttempts(PlayerAttempts);
    }
}

bool AChatPlayerController::ServerDecreasePlayerAttempts_Validate()
{
    return true; // 기본적으로 항상 유효하게 처리
}

void AChatPlayerController::MulticastUpdatePlayerAttempts_Implementation(int32 NewAttempts)
{
    PlayerAttempts = NewAttempts;

    if (IsLocalPlayerController() && ChatWidget)
    {
        // PlayerAttempts로 텍스트 갱신
        ChatWidget->UpdateAttemptsText(PlayerAttempts);
    }
}

void AChatPlayerController::OnRestartGame()
{
    // 서버에서 게임을 재시작하는 함수 호출
    if (HasAuthority())
    {
        ServerRestartGame();
    }
}

void AChatPlayerController::OnExitGame()
{
    // 게임 종료 로직
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    if (PlayerController)
    {
        PlayerController->ConsoleCommand(TEXT("quit"));
    }
}

void AChatPlayerController::ServerRestartGame_Implementation()
{
    // 서버에서 모든 클라이언트에 게임 재시작 요청을 보냄
    MulticastRestartGame();
}

bool AChatPlayerController::ServerRestartGame_Validate()
{
    return true;  // 실제 검증 로직이 필요할 경우 작성
}

void AChatPlayerController::MulticastRestartGame_Implementation()
{
    // 현재 레벨 이름을 얻어옴
    FString CurrentLevelName = GetWorld()->GetMapName();

    // "maps/" 부분을 잘라내고 레벨 이름만 추출
    CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

    // 서버 트래블을 통해 현재 레벨을 재시작
    FString TravelURL = CurrentLevelName + "?listen";  // ?listen을 통해 서버가 리스너 모드로 작동하도록 설정
    
    GetWorld()->ServerTravel(TravelURL);
}
