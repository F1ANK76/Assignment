// Fill out your copyright notice in the Description page of Project Settings.


#include "ScaleActor.h"

// Sets default values
AScaleActor::AScaleActor()
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
void AScaleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScaleActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector CurrentScale = GetActorScale3D();  // 현재 스케일 값을 가져옵니다.

    // 스케일을 변경할 기준 속도를 설정합니다.
    float ScaleChangeAmount = ScaleSpeed * DeltaTime;

    // 스케일의 최대 범위와 최소 범위에 도달했을 때 반전
    if (CurrentScale.X >= MaxScaleRange || CurrentScale.X <= MinScaleRange)
    {
        IsReverse = !IsReverse;
    }

    // 반전 상태에 따라 스케일을 증가시키거나 감소
    FVector NewScale = CurrentScale + (IsReverse ? -ScaleChangeAmount : ScaleChangeAmount);
    
    // X, Y, Z 축 모두 Clamp하여 범위를 제한합니다.
    NewScale.X = FMath::Clamp(NewScale.X, MinScaleRange, MaxScaleRange);
    NewScale.Y = FMath::Clamp(NewScale.Y, MinScaleRange, MaxScaleRange);
    NewScale.Z = FMath::Clamp(NewScale.Z, MinScaleRange, MaxScaleRange);

    // 최종적으로 스케일을 설정합니다.
    SetActorScale3D(NewScale);
}



