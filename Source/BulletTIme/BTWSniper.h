// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BulletTime.h"
#include "BTWeapon.h"
#include "Bullet.h"
#include "BTWSniper.generated.h"

/**
 *
 */
UCLASS()
class BULLETTIME_API ABTWSniper : public ABTWeapon
{
	GENERATED_BODY()

public:
	ABTWSniper();
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
	bool CanFire;
};
