// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BulletTime.h"
#include "Bullet.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "BTWeapon.generated.h"

UCLASS()
class BULLETTIME_API ABTWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABTWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	virtual void StartAttack();
	virtual void StopAttack();

	UPROPERTY(VisibleAnywhere, Category = Weapon)
		USkeletalMeshComponent* Weapon;
	float DamageMultiplier;

	bool IsMainWeapon;
};
