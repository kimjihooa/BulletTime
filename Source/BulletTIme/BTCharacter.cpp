// Fill out your copyright notice in the Description page of Project Settings.


#include "BTCharacter.h"


// Sets default values
ABTCharacter::ABTCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//PrimaryActorTick.bStartWithTickEnabled = false;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("BTCharacter"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 450.0f;
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SM_BODY(TEXT("/Engine/Tutorial/SubEditors/TutorialAssets/Character/TutorialTPP.TutorialTPP"));
	if (SM_BODY.Succeeded())
	{
		USkeletalMeshComponent* MyMesh = GetMesh();
		MyMesh->SetSkeletalMesh(SM_BODY.Object);
		MyMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		MyMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CHARACTER MESH NOT LOADED!!"))
	}

	AimModeLength = 150.0f;
	AimModeLo = FVector(0.0f, 100.0f, 70.0f);
	NormalModeLength = 350.0f;
	NormalModeLo = FVector::ZeroVector;
	ArmSpeed = 10.0f;
	LengthTo = NormalModeLength;
	LoTo = NormalModeLo;
}

// Called when the game starts or when spawned
void ABTCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABTCharacter::SetWeapon(ABTWeapon* NewWeapon)
{
	FName WeaponSocket(TEXT("middle_01_rSocket"));
	if (NewWeapon != nullptr)
	{
		if(CurrentWeapon != nullptr)
			CurrentWeapon->Destroy();
		NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		NewWeapon->SetOwner(this);
		CurrentWeapon = NewWeapon;
	}
}

// Called every frame
void ABTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, LengthTo, DeltaTime, ArmSpeed);
	SpringArm->SetRelativeLocation(FMath::VInterpTo(SpringArm->GetRelativeLocation(), LoTo, DeltaTime, ArmSpeed));
}

// Called to bind functionality to input
void ABTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABTCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABTCharacter::StopJump);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ABTCharacter::StartAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ABTCharacter::StopAim);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ABTCharacter::StartAttack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ABTCharacter::StopAttack);
	PlayerInputComponent->BindAxis("LookUp", this, &ABTCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ABTCharacter::Turn);
	PlayerInputComponent->BindAxis("UPDown", this, &ABTCharacter::UpDown);
	PlayerInputComponent->BindAxis("LeftRight", this, &ABTCharacter::LeftRight);
}

void ABTCharacter::StartJump()
{
	bPressedJump = true;
}
void ABTCharacter::StopJump()
{
	bPressedJump = false;
}
void ABTCharacter::StartAim()
{
	LengthTo = AimModeLength;
	LoTo = AimModeLo;
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->MaxWalkSpeed = 350.0f;
}
void ABTCharacter::StopAim()
{
	LengthTo = NormalModeLength;
	LoTo = NormalModeLo;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}
void ABTCharacter::UpDown(float AxisValue)
{
	AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), AxisValue);
}
void ABTCharacter::LeftRight(float AxisValue)
{
	AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), AxisValue);
}
void ABTCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}
void ABTCharacter::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ABTCharacter::StartAttack()
{
	if(CurrentWeapon != nullptr)
		CurrentWeapon->StartAttack();
}
void ABTCharacter::StopAttack()
{
	if (CurrentWeapon != nullptr)
		CurrentWeapon->StopAttack();
}