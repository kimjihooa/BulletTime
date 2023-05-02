// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BulletTime.h"
#include "BTWeapon.h"
#include "BTWCharger.generated.h"

/**
 * 
 */
UCLASS()
class BULLETTIME_API ABTWCharger : public ABTWeapon
{
	GENERATED_BODY()

public:
	ABTWCharger();
	UFUNCTION()
		virtual void StartAttack() override;
	UFUNCTION()
		virtual void StopAttack() override;
	UFUNCTION()
		void Charge();
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UArrowComponent* Arrow;
	UPROPERTY(EditAnywhere)
		float ChargeRate;
	float ChargeAmount;
	FTimerHandle FireTimerHandle;
};

