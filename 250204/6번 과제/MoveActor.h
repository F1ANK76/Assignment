// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveActor.generated.h"

UCLASS()
class SPARTAPROJECT_API AMoveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Properties")
	float MoveSpeed = 1500;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Properties")
	float MaxMoveRange = 2000;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Properties")
	bool IsReverse = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle TimerHandle;  // 타이머 핸들

	// 발판을 숨기고 보이게 하는 함수
	void TogglePlatformVisibility();

	bool bIsHidden = false;  // 발판이 숨겨져 있는지 여부를 추적
};

