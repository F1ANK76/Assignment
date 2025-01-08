// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Engine/Engine.h"
#include "Math/Vector.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 초기 좌표 설정
	CurrentPosition = FVector(0, 0, 0);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	// 이동 함수 호출 (10번 이동)
	Move();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 이동 함수
void AMyActor::Move()
{
	// 10번 이동
	for (int i = 0; i < 10; ++i)
	{
		// 각 이동 시 step 함수로 이동 값을 계산
		int32 StepX = Step();
		int32 StepY = Step();

		// 새로운 좌표 계산
		CurrentPosition.X += StepX;
		CurrentPosition.Y += StepY;

		// 좌표 출력 (UE_LOG 활용)
		UE_LOG(LogTemp, Warning, TEXT("Move %d: Current Position: (%f, %f)"), i + 1, CurrentPosition.X, CurrentPosition.Y);
	}
}

// step 함수 - 0 또는 1을 랜덤으로 반환
int32 AMyActor::Step()
{
	// 0 또는 1을 랜덤으로 반환
	return FMath::RandRange(0, 1);
}
