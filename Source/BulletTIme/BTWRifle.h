// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BulletTime.h"
#include "BTWeapon.h"
#include "Bullet.h"
#include "BTWRifle.generated.h"

/**
 * 
 */
UCLASS()
class BULLETTIME_API ABTWRifle : public ABTWeapon
{
	GENERATED_BODY()
	
public:
	ABTWRifle();
	UFUNCTION()
		virtual void StartAttack() override;
	UFUNCTION()
		virtual void StopAttack() override;
	UFUNCTION()
		void Fire();
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UArrowComponent* Arrow;
	UPROPERTY(EditAnywhere)
		float FireRate;
	FTimerHandle FireTimerHandle;
};
