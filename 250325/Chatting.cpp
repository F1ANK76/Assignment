// Chatting.cpp

#include "Chatting.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "ChatPlayerController.h"
#include "GameFramework/PlayerState.h"

void UChatting::NativeConstruct()
{
    Super::NativeConstruct();

    // 버튼 클릭 이벤트 설정
    if (SendButton)
    {
        SendButton->OnClicked.AddDynamic(this, &UChatting::OnSendButtonClicked);
    }
}

void UChatting::OnSendButtonClicked()
{
    FString Message = ChatText->GetText().ToString();

    if (!Message.IsEmpty())
    {
        // 플레이어 컨트롤러 가져오기
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        AChatPlayerController* ChatPlayerController = Cast<AChatPlayerController>(PlayerController);

        if (ChatPlayerController && ChatPlayerController->PlayerAttempts > 0)
        {
            ChatPlayerController->ServerDecreasePlayerAttempts();

            APlayerState* PlayerState = ChatPlayerController->GetPlayerState<APlayerState>();

            if (PlayerState)
            {
                FString HostName = PlayerState->GetPlayerName(); // 플레이어 이름 얻기
                FString FinalMessage = HostName + ": " + Message; // "호스트: 메시지" 형태로 구성

                // 서버로 메시지를 전송
                ChatPlayerController->ServerSendChatMessage(FinalMessage);
            }

            // 텍스트 필드 초기화
            ChatText->SetText(FText::GetEmpty());
        }
    }
}

void UChatting::AddChatMessage(const FString& Message)
{
    if (ChatScrollBox)
    {
        UTextBlock* NewMessage = NewObject<UTextBlock>(this);
        NewMessage->SetText(FText::FromString(Message));
        ChatScrollBox->AddChild(NewMessage);
    }
}

void UChatting::UpdateAttemptsText(int32 NewAttempts)
{
    if (AttemptsBlock)
    {
        FString AttemptsText = FString::Printf(TEXT("Send Attempts : %d"), NewAttempts);
        AttemptsBlock->SetText(FText::FromString(AttemptsText));  // 텍스트 블록 갱신
    }
}
