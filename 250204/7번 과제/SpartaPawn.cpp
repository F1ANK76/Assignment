// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "SpartaPlayerController.h"

// Sets default values
ASpartaPawn::ASpartaPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// 1. 기본 캡슐 컴포넌트 생성
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));

	// 2. 캡슐 컴포넌트를 루트 컴포넌트로 설정
	SetRootComponent(CapsuleComp);

	// 3. 스켈레탈 메쉬 컴포넌트 생성
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));

	// 4. 스켈레탈 메쉬 컴포넌트를 캡슐 컴포넌트의 자식으로 설정
	SkeletalMeshComp->SetupAttachment(CapsuleComp);

	// 5. 스프링 암 생성
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	// 스프링 암을 루트 컴포넌트 (CapsuleComponent)에 부착
	SpringArmComp->SetupAttachment(RootComponent);
	// 캐릭터와 카메라 사이의 거리 기본값 300으로 설정
	SpringArmComp->TargetArmLength = 300;
	// 컨트롤러 회전에 따라 스프링 암도 회전하도록 설정
	//SpringArmComp->bUsePawnControlRotation = true; // 폰 자체 회전시 해당 옵션 비활성화 해야함

	// 6. 카메라 컴포넌트 생성
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	// 스프링 암의 소켓 위치에 카메라를 부착 (SocketName은 SpringArmComp의 끝 부분을 가르킴)
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	// 카메라는 스프링 암의 회전을 따르므로 PawnControlRotation은 꺼둠
	//CameraComp->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ASpartaPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpartaPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASpartaPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Enhanced InputComponent로 캐스팅
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// IA를 가져오기 위해 현재 소유 중인 Controller를 ASpartaPlayerController로 캐스팅
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				// IA_Move 액션 키를 "키를 누르고 있는 동안" Move() 호출
				EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &ASpartaPawn::Move);
			}

			if (PlayerController->LookAction)
			{
				// IA_Look 액션 마우스가 "움직일 때" Look() 호출
				EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &ASpartaPawn::Look);
			}
		}
	}
}

void ASpartaPawn::Move(const FInputActionValue& value)
{
	const FVector2D MoveInput = value.Get<FVector2D>();

	// 캐릭터의 회전 값 얻기
	FVector ForwardDirection = GetActorForwardVector();
	FVector RightDirection = GetActorRightVector();

	// X, Y축 이동값 계산 후 월드 좌표로 이동 적용
	if (FMath::IsNearlyZero(MoveInput.X) == false)
	{
		FVector Movement = ForwardDirection * MoveInput.X * NormalSpeed * GetWorld()->GetDeltaSeconds();
		AddActorWorldOffset(Movement, true);
	}

	if (FMath::IsNearlyZero(MoveInput.Y) == false)
	{
		FVector Movement = RightDirection * MoveInput.Y * NormalSpeed * GetWorld()->GetDeltaSeconds();
		AddActorWorldOffset(Movement, true);
	}
}

void ASpartaPawn::Look(const FInputActionValue& value)
{
	// 마우스의 X, Y 움직임을 2D 축으로 가져옴
	FVector2D LookInput = value.Get<FVector2D>();

	// 좌우 회전만 적용 (Yaw, 캐릭터가 상하로 회전하면 이상함)
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw += LookInput.X;  // 마우스 X값에 맞게 Yaw값 변경

	// 회전 적용 (Pawn 자체의 로컬 회전)
	SetActorRotation(CurrentRotation);  // 이 회전값을 Pawn에 적용

	// 상하 회전은 캐릭터를 회전시키지 않고 SpringArmRotation만 설정
	FRotator SpringArmRotation = SpringArmComp->GetComponentRotation();

	SpringArmRotation.Pitch -= LookInput.Y;

	// 상하 회전 제한 (최대 -85도, 최소 85도)
	SpringArmRotation.Pitch = FMath::Clamp(SpringArmRotation.Pitch, -85.0f, 85.0f);

	SpringArmComp->SetWorldRotation(SpringArmRotation);
}

