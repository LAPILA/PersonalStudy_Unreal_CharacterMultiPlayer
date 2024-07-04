// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() 
{
	//ƽ Ȱ��ȭ
	PrimaryActorTick.bCanEverTick = true;
	//������ Ȱ��ȭ
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		//������ �������� �������� Ŭ��� ������
		SetReplicateMovement(true);
	}
}

void AMovingPlatform::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) {
		//ƽ�� ��ġ�� �ް�
		FVector Location = GetActorLocation();
		FVector GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
		//ƽ�� ������ �ް�
		//���ڰ� ������ ��ȣ���ִ� SafeNormal
		FVector Direction = (GlobalTargetLocation - Location).GetSafeNormal();
		// �ӵ� * �ʴ�ð� * ����
		Location += Speed * DeltaTime * Direction;
		//�ش� ��ġ�� �缳��
		SetActorLocation(Location);
	}
}


