// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BulletTime.h"
#include "GameFramework/Character.h"
#include <Engine/Classes/Components/CapsuleComponent.h>
#include <Engine/Classes/Camera/CameraComponent.h>
#include <Engine/Classes/GameFramework/CharacterMovementComponent.h>
#include <Engine/Classes/GameFramework/SpringArmComponent.h>
#include "BTWeapon.h"
#include "BTCharacter.generated.h"

UCLASS()
class BULLETTIME_API ABTCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABTCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
		UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
		USpringArmComponent* SpringArm;
	void SetWeapon(class ABTWeapon* NewWeapon);
	UPROPERTY(Visibleanywhere, Category = Weapon)
		class ABTWeapon* CurrentWeapon;
	UPROPERTY(Visibleanywhere, Category = Weapon)
		class ABTWeapon* MainWeapon;
	UPROPERTY(Visibleanywhere, Category = Weapon)
		class ABTWeapon* SubWeapon;
	UFUNCTION()
		void StartAttack();
	UFUNCTION()
		void StopAttack();
	UFUNCTION()
		void HoldWeapon();
	UFUNCTION()
		void PutWeapon();
	UFUNCTION()
		void ChangeWeapon();

private:
	void StartJump();
	void StopJump();
	void StartAim();
	void StopAim();
	void UpDown(float AxisValue);
	void LeftRight(float AxisValue);
	void LookUp(float AxisValue);
	void Turn(float AxisValue);

	float AimModeLength;
	float NormalModeLength;
	float LengthTo;
	FVector AimModeLo;
	FVector NormalModeLo;
	FVector LoTo;
	float ArmSpeed;
};
