// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() 
{
	//틱 활성화
	PrimaryActorTick.bCanEverTick = true;
	//움직임 활성화
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		//액터의 움직임이 서버에서 클라로 복제됨
		SetReplicateMovement(true);
	}
}

void AMovingPlatform::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) {
		//틱당 위치를 받고
		FVector Location = GetActorLocation();
		FVector GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
		//틱당 방향을 받고
		//숫자가 작을때 보호해주는 SafeNormal
		FVector Direction = (GlobalTargetLocation - Location).GetSafeNormal();
		// 속도 * 초당시간 * 방향
		Location += Speed * DeltaTime * Direction;
		//해당 위치를 재설정
		SetActorLocation(Location);
	}
}


