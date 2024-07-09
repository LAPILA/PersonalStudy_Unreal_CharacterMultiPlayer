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
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(const float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if(ActiveTriggers > 0)
	{
		if (HasAuthority()) {
			//ƽ�� ��ġ�� �ް�
			FVector Location = GetActorLocation();
			float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float JourneyTravelled = (Location - GlobalStartLocation).Size();

			if (JourneyTravelled > JourneyLength)
			{
				FVector Swap = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = Swap;
			}
			//���ڰ� ������ ��ȣ���ִ� SafeNormal
			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			// �ӵ� * �ʴ�ð� * ����
			Location += Speed * DeltaTime * Direction;
			//�ش� ��ġ�� �缳��
			SetActorLocation(Location);
		}
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
}

