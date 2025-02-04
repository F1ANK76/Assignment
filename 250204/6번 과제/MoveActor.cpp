// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveActor.h"
#include "TimerManager.h"

// Sets default values
AMoveActor::AMoveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Scene 컴포넌트 생성
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	// 해당 컴포넌트 루트로 설정
	SetRootComponent(SceneRoot);

	// StaticMesh 컴포넌트 생성
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	// 해당 컴포넌트를 루트 컴포넌트에 연결
	StaticMeshComp->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void AMoveActor::BeginPlay()
{
	Super::BeginPlay();

    // 발판이 숨겨지거나 보이게 할 주기 설정 (예: 3초 후에 숨기고, 3초 후에 다시 보이게)
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMoveActor::TogglePlatformVisibility, 3.0f, true);
}

// Called every frame
void AMoveActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 현재 위치 가져오기
    FVector CurrentLocation = GetActorLocation();
    float CurrentY = CurrentLocation.Y;

    // 목표 이동 거리
    float MoveAmount = MoveSpeed * DeltaTime;

    // IsReverse에 따라 이동 방향을 결정
    if (IsReverse)
    {
        MoveAmount = -MoveAmount;  // 반전 상태일 경우 이동 방향을 반대로
    }

    // 이동 후 위치가 Max 범위를 넘지 않도록 제어
    if (CurrentY + MoveAmount >= MaxMoveRange || CurrentY + MoveAmount <= -MaxMoveRange)
    {
        // 움직임의 결과값이 범위를 넘길시 최소와 최대 범위 내에 위치하도록 적용
        CurrentLocation.Y = FMath::Clamp(CurrentY + MoveAmount, -MaxMoveRange, MaxMoveRange);

        // 반전 상태 토글
        IsReverse = !IsReverse;
    }
    else
    {
        // 반전하지 않으면 이동
        CurrentLocation.Y += MoveAmount;
    }

    // 최종적으로 위치 반영
    SetActorLocation(CurrentLocation);
}

void AMoveActor::TogglePlatformVisibility()
{
    if (bIsHidden)
    {
        // 발판을 보이게 함
        SetActorHiddenInGame(false);
        bIsHidden = false;
    }
    else
    {
        // 발판을 숨김
        SetActorHiddenInGame(true);
        bIsHidden = true;
    }
}



