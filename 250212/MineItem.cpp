// Fill out your copyright notice in the Description page of Project Settings.


#include "MineItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AMineItem::AMineItem()
{
	ExplosionDelay = 1;
	ExplosionRadius = 210;
	ExplosionDamage = 50;

	ItemType = "Mine";
	bHasExploded = false;

	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(ExplosionRadius);
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(Scene);
}

void AMineItem::ActivateItem(AActor* Activator)
{
	// 게임 월드 -> 타이머 매니저가 존재
	// 타이머 핸들러

	if (bHasExploded) return;

	Super::ActivateItem(Activator);

	GetWorld()->GetTimerManager().SetTimer(ExplosionTimerHandle, this, &AMineItem::Explode, ExplosionDelay, false);

	bHasExploded = true;
}

void AMineItem::Explode()
{
	UParticleSystemComponent* Particle = nullptr;

	if (ExplosionParticle)
	{
		Particle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ExplosionParticle,
			GetActorLocation(),
			GetActorRotation(),
			false
		);
	}

	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			ExplosionSound,
			GetActorLocation()
		);
	}

	TArray<AActor*> OverlappingActors;
	ExplosionCollision->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			UGameplayStatics::ApplyDamage(
				Actor,
				ExplosionDamage,
				nullptr,
				this,
				UDamageType::StaticClass()
			);
		}
	}

	DestroyItem();

	// 파티클 삭제
	if (Particle)
	{
		FTimerHandle DestroyParticleTimerHandle;

		// weak 참조로 캡처 (타이머 실행시 객체가 유효하지 않으면 아무 작업도 하지 않음)
		TWeakObjectPtr<UParticleSystemComponent> WeakParticle = Particle;

		GetWorld()->GetTimerManager().SetTimer(
			DestroyParticleTimerHandle,
			[WeakParticle]()
			{
				// weak 참조로 캡처했으므로 객체가 유효하지 않으면 바로 리턴
				if (!WeakParticle.IsValid())
				{
					UE_LOG(LogTemp, Warning, TEXT("No Valid Mine"));
					return;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Valid Mine"));
					WeakParticle->DestroyComponent();
				}
			},
			0.1f,
			false
		);

		//GetWorld()->GetTimerManager().SetTimer(
		//	DestroyParticleTimerHandle,
		//	[Particle]() // 람다 함수
		//	{
		//		Particle->DestroyComponent();
		//	},
		//	0.1f,
		//	false
		//);
	}
}
