// ChatPlayerController.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ChatPlayerController.generated.h"

class UChatting;

UCLASS()
class SPARTAPROJECT_API AChatPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    AChatPlayerController();

    // 승리 여부를 나타내는 변수
    UPROPERTY(BlueprintReadWrite, Category = "GameState")
    bool bIsWinner;

    // WBP_Chatting을 참조할 수 있는 변수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> WBP_Chatting; // 위젯 Blueprint를 C++에서 참조

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> GameOverUIClass;

    UPROPERTY()
    UUserWidget* GameOverUIWidget;

    UPROPERTY()
    UChatting* ChatWidget; // 위젯 변수로 저장

    // 플레이어의 시도 횟수
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Stats")
    int32 PlayerAttempts;

    virtual void BeginPlay() override;

    // 위젯을 뷰포트에 추가하는 함수
    void ShowChatWidget();

    // 게임 재시작 함수 선언
    UFUNCTION()
    void OnRestartGame();

    // 게임 종료 함수 선언
    UFUNCTION()
    void OnExitGame();

    // PlayerAttempts 감소 요청을 서버에 전달하는 함수
    UFUNCTION(Server, Reliable, WithValidation)
    void ServerDecreasePlayerAttempts();

    UFUNCTION(Client, Reliable)
    void DisplayGameOverUI(const FString& Message);

    // 서버로 채팅 메시지를 전송하는 함수
    UFUNCTION(Server, Reliable, WithValidation)
    void ServerSendChatMessage(const FString& Message);

    // 클라이언트에 메시지를 전송하는 함수
    UFUNCTION(Client, Reliable)
    void ClientReceiveChatMessage(const FString& Message);

    // 서버에서 클라이언트로 시도 횟수를 업데이트하는 내용을 모든 클라이언트에게 전송하는 기능을 수행
    UFUNCTION(NetMulticast, Reliable)
    void MulticastUpdatePlayerAttempts(int32 NewAttempts);

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerRestartGame();

    UFUNCTION(NetMulticast, Reliable)
    void MulticastRestartGame();

    bool ServerSendChatMessage_Validate(const FString& Message);
    void ServerSendChatMessage_Implementation(const FString& Message);
    void ClientReceiveChatMessage_Implementation(const FString& Message);
    void DisplayGameOverUI_Implementation(const FString& Message);

    void ServerDecreasePlayerAttempts_Implementation();
    bool ServerDecreasePlayerAttempts_Validate();

    void MulticastUpdatePlayerAttempts_Implementation(int32 NewAttempts);

    void ServerRestartGame_Implementation();
    bool ServerRestartGame_Validate();
    void MulticastRestartGame_Implementation();
};
