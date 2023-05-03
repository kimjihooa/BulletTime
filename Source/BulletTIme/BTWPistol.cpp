// Fill out your copyright notice in the Description page of Project Settings.


#include "BTWPistol.h"

ABTWPistol::ABTWPistol()
{
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;
	Weapon->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ARROW"));
	Arrow->SetupAttachment(Weapon);
	Arrow->SetRelativeLocation(FVector(0.0f, -200.0f, 0.0f));
	Arrow->SetRelativeRotation(FRotator(0.0f, -90.0f, -90.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_WEAPON(TEXT("/Engine/EngineMeshes/SkeletalCube.SkeletalCube"));
	if (SK_WEAPON.Succeeded())
	{
		Weapon->SetSkeletalMesh(SK_WEAPON.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon Skeletal Mesh Not Loaded!"));
	}
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));

	IsMainWeapon = false;
	FireRate = 0.5f;
	CanFire = true;
	DamageMultiplier = 0.5f;
}

void ABTWPistol::StartAttack()
{
	if (CanFire)
	{
		CanFire = false;
		FVector Location = Arrow->GetComponentLocation();
		FRotator Rotation = Arrow->GetComponentRotation();
		//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), Arrow->GetComponentRotation().Pitch, Arrow->GetComponentRotation().Roll, Arrow->GetComponentRotation().Yaw);
		auto Bullet = GetWorld()->SpawnActor<ABullet>(ABullet::StaticClass(), Location, Rotation);
		if (Bullet != nullptr)
			Bullet->DamageMultiplier = 2.0f;
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ABTWPistol::Fire, FireRate, false);
	}
}
void ABTWPistol::Fire()
{
	CanFire = true;
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}
void ABTWPistol::StopAttack()
{

}