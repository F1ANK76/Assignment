// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScaleActor.generated.h"

UCLASS()
class SPARTAPROJECT_API AScaleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScaleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Properties")
	float ScaleSpeed = 25;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Properties")
	float MaxScaleRange = 50;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Properties")
	float MinScaleRange = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Properties")
	bool IsReverse = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

