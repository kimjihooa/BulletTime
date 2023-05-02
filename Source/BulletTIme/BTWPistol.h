// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTWeapon.h"
#include "BTWPistol.generated.h"

/**
 * 
 */
UCLASS()
class BULLETTIME_API ABTWPistol : public ABTWeapon
{
	GENERATED_BODY()

public:
	ABTWPistol();
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
