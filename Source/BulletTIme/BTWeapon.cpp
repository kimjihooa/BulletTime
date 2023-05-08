// Fill out your copyright notice in the Description page of Project Settings.


#include "BTWeapon.h"

// Sets default values
ABTWeapon::ABTWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DamageMultiplier = 0.0f;
	IsMainWeapon = true;
}

// Called when the game starts or when spawned
void ABTWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
//void ABTWeapon::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void ABTWeapon::StartAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack Started!!"));
}
void ABTWeapon::StopAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack Stopped!!"));
}
