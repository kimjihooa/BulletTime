// Fill out your copyright notice in the Description page of Project Settings.


#include "BTWeapon.h"

// Sets default values
ABTWeapon::ABTWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

	DamageMultiplier = 0.0f;

	CurrentWeapon = None;
}
enum ABTWeapon::WeaponType
{
	None,
	Rapid,
	Single,
	Charge
};

void ABTWeapon::SetWeapon(WeaponType Type)
{
	if (CurrentWeapon == Type)
		return;
	if (StartAttackDelegate.IsBound())
		StartAttackDelegate.Unbind();
	if (StopAttackDelegate.IsBound())
		StopAttackDelegate.UnBind();
	switch (Type)
	{
	case None:
		break;

	case Rapid:
		StartAttackDelegate.BindUFunction(this, FName("RapidStart"));
		StopAttackDelegate.BindUFunction(this, FName("RapidEnd"));
		DamageMultiplier = 1.0f;
		break;
	}
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

void ABTWeapon::RapidStart()
{

}
void ABTWeapon::RapidStop()
{

}

/*
void ABTWRifle::StartAttack()
{
	FVector Location = Arrow->GetComponentLocation();
	FRotator Rotation = Arrow->GetComponentRotation();
	//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), Arrow->GetComponentRotation().Pitch, Arrow->GetComponentRotation().Roll, Arrow->GetComponentRotation().Yaw);

	GetWorld()->SpawnActor<ABullet>(ABullet::StaticClass(), Location, Rotation);
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ABTWRifle::Fire, FireRate, true);
}
void ABTWRifle::Fire()
{
	FVector Location = Arrow->GetComponentLocation();
	FRotator Rotation = Arrow->GetComponentRotation();
	//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), Arrow->GetComponentRotation().Pitch, Arrow->GetComponentRotation().Roll, Arrow->GetComponentRotation().Yaw);

	auto Bullet = GetWorld()->SpawnActor<ABullet>(ABullet::StaticClass(), Location, Rotation);
	if (Bullet != nullptr)
		Bullet->DamageMultiplier = 1.0f;
}
void ABTWRifle::StopAttack()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}*/