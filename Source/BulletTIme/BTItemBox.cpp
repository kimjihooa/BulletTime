// Fill out your copyright notice in the Description page of Project Settings.


#include "BTItemBox.h"

// Sets default values
ABTItemBox::ABTItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	Mesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	Trigger->SetBoxExtent(FVector(30.0f, 30.0f, 30.0f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> 
		SM_BOX(TEXT("/Engine/EditorMeshes/ArcadeEditorSphere.ArcadeEditorSphere"));
	if (SM_BOX.Succeeded())
	{
		Mesh->SetStaticMesh(SM_BOX.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemBox Mesh Not Loaded!"));
	}
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -5.0f));

	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	WeaponClass = ABTWeapon::StaticClass();
}

// Called when the game starts or when spawned
void ABTItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABTItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ABTItemBox::OnCharacterOverlap);
}

void ABTItemBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABTCharacter* BTCharacter = Cast<ABTCharacter>(OtherActor);
	if (BTCharacter != nullptr && WeaponClass != nullptr)
	{
		ABTWeapon* NewWeapon = GetWorld()->SpawnActor<ABTWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
		BTCharacter->SetWeapon(NewWeapon);
		UE_LOG(LogTemp, Warning, TEXT("Weapon Changed!"));
	}
}

// Called every frame
//void ABTItemBox::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

