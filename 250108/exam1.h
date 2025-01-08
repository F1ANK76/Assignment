// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class UNREAL5_GAMEBP_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 캐릭터의 현재 좌표
	FVector CurrentPosition;

	// 10번 이동을 처리하는 함수
	void Move();

	// 랜덤 이동값을 반환하는 step 함수
	int32 Step();
};
