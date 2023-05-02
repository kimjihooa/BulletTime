// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("COLLIDER"));
	Collider->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	Collider->SetCollisionProfileName("Bullet");
	//Collider->OnComponentBeginOverlap.AddDynamic(this, &ABullet::BeginOverlap);
	SetRootComponent(Collider);
	
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Mesh->SetupAttachment(Collider);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SM_BULLET(TEXT("/Engine/EditorMeshes/ArcadeEditorSphere.ArcadeEditorSphere"));
	if (SM_BULLET.Succeeded())
	{
		Mesh->SetStaticMesh(SM_BULLET.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BULLET MESH NOT LOADED!!"));
	}
	Mesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	Speed = 1000.0f;
	Atk = 2.0f;
	DamageMultiplier = 0.0f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * Speed * DeltaTime);
}