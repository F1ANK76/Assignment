# 게임 루프 및 UI 재설계 과제 구현

**1. 멀티 웨이브 구조 구현**

- 한 레벨 안에서 최소 3단계 이상의 웨이브를 만들기 위하여 기존에 웨이브가 바뀔때마다 다른 맵을 넣었는데 해당 부분을 하나의 맵으로 고정

```
if (CurrentLevelIndex >= MaxLevels)
{
	OnGameOver();
	return;
}
else
{
	// 한 레벨만 재실행
	UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[0]);
}
```

- 웨이브가 증가할수록 스폰되는 아이템의 개수가 많아지면서 코인을 더 많이 주워야 클리어가 되도록 구현

```
// Wave에 따른 스폰 아이템 개수 조정
if (CurrentLevelIndex == 0) ItemToSpawn = 10;
else if(CurrentLevelIndex == 1) ItemToSpawn = 20;
else if (CurrentLevelIndex == 2) ItemToSpawn = 30;

for (int32 i = 0; i < ItemToSpawn; i++)
{
	if (FoundVolumes.Num() > 0)
	{
		ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);

		if (SpawnVolume)
		{
			AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();

			if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
			{
				SpawnedCoinCount++;
			}
		}
	}
}
```

**2. HUD & 메뉴 UI 리뉴얼**

- HUD에 현재 맵에 스폰된 모든 코인 개수와 획득한 코인 개수를 확인할 수 있도록 UI 배치
- 게임을 종료할 수 있도록 시작 버튼 옆에 종료 버튼을 추가
- 블루프린트 Quit Game 노드를 이용하여 기능 구현

### 기타 수정 사항

**1. UI 관련 요소**

- 스폰되는 영역이 너무 커서 해당 영역 축소 작업 진행
- 보통 게임에서 지뢰나 회복 포션이 엄청 드랍되지는 않는 편이여서 해당 부분 확률 수정
- 지뢰가 바로 터져야 플레이 난이도가 상승해서 해당 부분 수정 및 지뢰 데미지 증가
- 자신의 모니터 사이즈에 맞게끔 border 영역 수정 (24 -> 27인치 사이즈로 변경)
- 스폰 코인 개수와 획득 코인 개수를 UI에서 볼 수 있도록 텍스트 추가

**2. 로직 관련 요소**

- 지뢰 데미지로 인한 게임 오버시 지뢰 파티클이 삭제되지 않은 상태에서 게임을 다시 시작하면 이전 파티클이 초기화 되면서 해당 파티클 삭제 명령이 작동하면서 오류가 나는 것 같다는 느낌을 받음
- TWeakObjectPtr<UParticleSystemComponent> WeakParticle을 이용하여 객체가 유효하지 않으면 리턴할 수 있도록 조건 추가

```
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
```

- GameState.cpp BeginPlay에서 StartLevel을 바로 실행하면 맨 처음에 메뉴 화면이 떠있어도 게임이 내부적으로 진행돼서 LevelDuration만큼 시간이 흐르면 Start 버튼을 누르지 않아도 자동으로 다음 Wave로 화면이 전환됨
- SpartaGameInstance에 bGameStarted bool 변수를 추가해서 사용자가 Start 버튼을 눌러서 게임을 실행했을때만 게임이 진행되도록 구현

```
void ASpartaGameState::BeginPlay()
{
	Super::BeginPlay();

	// GameInstance를 통해 게임 시작 상태 확인
	USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GetWorld()->GetGameInstance());

	if (SpartaGameInstance && SpartaGameInstance->bGameStarted)
	{
		StartLevel();
		UE_LOG(LogTemp, Warning, TEXT("Game Start!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game has not started yet."));
	}

  // ...
}
```

### 최종 화면

![image](https://github.com/user-attachments/assets/db472988-bbfc-49ea-b54b-fb541c4e0f27)

