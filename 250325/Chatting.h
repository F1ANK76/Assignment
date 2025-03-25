// Chatting.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Chatting.generated.h"

UCLASS()
class SPARTAPROJECT_API UChatting : public UUserWidget
{
	GENERATED_BODY()
	
public:
    // 채팅 전송 버튼
    UPROPERTY(meta = (BindWidget))
    class UButton* SendButton;

    // 입력받는 텍스트 필드
    UPROPERTY(meta = (BindWidget))
    class UEditableText* ChatText;

    // 채팅 메시지 리스트를 표시할 스크롤 박스
    UPROPERTY(meta = (BindWidget))
    class UScrollBox* ChatScrollBox;

    // 텍스트 블록 (AttemptsBlock을 표시할 텍스트 블록)
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* AttemptsBlock;

    virtual void NativeConstruct() override;
    
    UFUNCTION()
    void OnSendButtonClicked();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void UpdateAttemptsText(int32 NewAttempts);

    void AddChatMessage(const FString& Message);
};
