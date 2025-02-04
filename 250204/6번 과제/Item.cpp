// Fill out your copyright notice in the Description page of Project Settings.
#include "Item.h"

// 생성자 부분 : C++ 클래스 객체가 메모리에 생성될 때 단 한 번 호출
AItem::AItem()
{
	// Scene 컴포넌트 생성
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	// 해당 컴포넌트 루트로 설정
	SetRootComponent(SceneRoot);

	// StaticMesh 컴포넌트 생성
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	// 해당 컴포넌트를 루트 컴포넌트에 연결
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;

	RotationSpeed = 90;
}

// 게임이 시작 (Play 모드)되거나, 런타임 중 액터가 새로 생성 (Spawn)되는 순간에 한 번 호출
void AItem::BeginPlay()
{
	Super::BeginPlay();

	OnItemPicked();
}

// 매 프레임마다 반복 호출되며, 실시간 업데이트가 필요한 로직 (캐릭터 이동, 물리 연산 등)을 넣음
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FMath::IsNearlyZero(RotationSpeed) == false)
	{
		// Pitch(Y), Yaw(Z), Roll(X) 축으로 회전
		AddActorLocalRotation(FRotator(0, RotationSpeed * DeltaTime, 0));
	}
}

void AItem::ResetActorPosition()
{
	SetActorLocation(FVector::ZeroVector);
}

float AItem::GetRotationSpeed() const
{
	return RotationSpeed;
}
