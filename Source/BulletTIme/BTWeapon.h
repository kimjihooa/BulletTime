// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BulletTime.h"
#include "Bullet.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "BTWeapon.generated.h"

DECLARE_DELEGATE(FStartAttackDelegate);
DECLARE_DELEGATE(FStopAttackDelegate);

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

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UArrowComponent* Arrow;

	virtual void StartAttack();
	FStartAttackDelegate StartAttackDelegate;
	virtual void StopAttack();
	FStopAttackDelegate StopAttackDelegete;

	enum WeaponType;
	void SetWeapon(WeaponType Type);
	WeaponType CurrentWeapon;

	UFUNCTION()
		void RapidStart();
	UFUNCTION()
		void RapidStop();

	UPROPERTY(VisibleAnywhere, Category = Weapon)
		USkeletalMeshComponent* Weapon;
	UPROPERTY(EditAnywhere)
		float DamageMultiplier;
	UPROPERTY(EditAnywhere)
		float Speed;
};
