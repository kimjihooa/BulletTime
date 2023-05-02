// Fill out your copyright notice in the Description page of Project Settings.


#include "BTWCharger.h"

ABTWCharger::ABTWCharger()
{
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;
	Weapon->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ARROW"));
	Arrow->SetupAttachment(Weapon);
	Arrow->SetRelativeLocation(FVector(0.0f, -200.0f, 0.0f));
	Arrow->SetRelativeRotation(FRotator(0.0f, -90.0f, -90.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_WEAPON(TEXT("/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh"));
	if (SK_WEAPON.Succeeded())
	{
		Weapon->SetSkeletalMesh(SK_WEAPON.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon Skeletal Mesh Not Loaded!"));
	}
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));

	ChargeRate = 0.1f;
	ChargeAmount = 0.01f;
	DamageMultiplier = 3.0f;
}
void ABTWCharger::StartAttack()
{
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ABTWCharger::Charge, ChargeRate, true);
}
void ABTWCharger::Charge()
{
	if (ChargeAmount < 0.1)
		ChargeAmount += 0.01f;
}
void ABTWCharger::StopAttack()
{
	float Energy = ChargeAmount * 10;
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	FVector Location = Arrow->GetComponentLocation();
	FRotator Rotation = Arrow->GetComponentRotation();
	auto Bullet = GetWorld()->SpawnActor<ABullet>(ABullet::StaticClass(), Location, Rotation);
	if (Bullet != nullptr)
	{
		Bullet->SetActorScale3D(FVector(Energy, Energy, Energy));
		Bullet->DamageMultiplier = Energy * DamageMultiplier;
	}
	UE_LOG(LogTemp, Warning, TEXT("Energy : %f"), Energy);
	ChargeAmount = 0.0f;
}