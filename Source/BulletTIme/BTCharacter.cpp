// Fill out your copyright notice in the Description page of Project Settings.


#include "BTCharacter.h"


// Sets default values
ABTCharacter::ABTCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance ifyou don't need it.
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
	if(SM_BODY.Succeeded())
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

	WalkSpeed = 600.0f;
	RunSpeed = 1000.0f;
	CrawlSpeed = 350.0f;
	SpeedMultiplier = 1.0f;
}

// Called when the game starts or when spawned
void ABTCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABTCharacter::SetWeapon(ABTWeapon* NewWeapon)
{
	if(NewWeapon != nullptr)
	{
		if(NewWeapon->IsMainWeapon)
		{
			if(MainWeapon != nullptr)
				MainWeapon->Destroy();
			MainWeapon = NewWeapon;
			MainWeapon->SetOwner(this);
			FName WeaponSocket(TEXT("spine_03Socket_main"));
			MainWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		}
		else
		{
			if(SubWeapon != nullptr)
				SubWeapon->Destroy();
			SubWeapon = NewWeapon;
			SubWeapon->SetOwner(this);
			FName WeaponSocket(TEXT("spine_03Socket_sub"));
			SubWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		}
	}
}
void ABTCharacter::ChangeWeapon()
{
	if (CurrentWeapon != nullptr) //If holding something
	{
		if (CurrentWeapon == MainWeapon) //If holding main
		{
			if (SubWeapon != nullptr)
			{
				CurrentWeapon = SubWeapon; //Change to sub
				if (MainWeapon != nullptr)
					MainWeapon->StopAttack();
				if (SubWeapon != nullptr)
					SubWeapon->StopAttack();
				HoldWeapon();

			}
		}
		else //If holding sub
		{
			if (MainWeapon != nullptr)
			{
				CurrentWeapon = MainWeapon; //Change to main
				if (MainWeapon != nullptr)
					MainWeapon->StopAttack();
				if (SubWeapon != nullptr)
					SubWeapon->StopAttack();
				HoldWeapon();
			}
		}
	}
	else //If holding nothing
	{
		if (MainWeapon != nullptr) //If Main existes
		{
			CurrentWeapon = MainWeapon;
			if (MainWeapon != nullptr)
				MainWeapon->StopAttack();
			if (SubWeapon != nullptr)
				SubWeapon->StopAttack();
			HoldWeapon();
			return;
		}
		if (SubWeapon != nullptr)
		{
			CurrentWeapon = SubWeapon; //If sub existes
			if (MainWeapon != nullptr)
				MainWeapon->StopAttack();
			if (SubWeapon != nullptr)
				SubWeapon->StopAttack();
			HoldWeapon();
			return;
		}
		return;
	}
}
void ABTCharacter::PutWeapon()
{
	CurrentWeapon = nullptr;
	if (MainWeapon != nullptr)
	{
		FName WeaponSocket = TEXT("spine_03Socket_main");
		MainWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		MainWeapon->StopAttack();
	}
	if (SubWeapon != nullptr)
	{
		FName WeaponSocket = TEXT("spine_03Socket_sub");
		SubWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		SubWeapon->StopAttack();
	}
}
void ABTCharacter::HoldWeapon()
{
	if (CurrentWeapon != nullptr)
	{
		if (CurrentWeapon == MainWeapon)
		{
			FName WeaponSocket(TEXT("middle_01_rSocket"));
			MainWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
			MainWeapon->SetActorRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));  //Delete this later!!!!!!!!!!
			if (SubWeapon != nullptr)
			{
				WeaponSocket = TEXT("spine_03Socket_sub");
				SubWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
				SubWeapon->SetActorRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));  //Delete this later!!!!!!!!!!
			}
		}
		else
		{
			FName WeaponSocket(TEXT("middle_01_rSocket"));
			SubWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
			SubWeapon->SetActorRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));  //Delete this later!!!!!!!!!!
			if (MainWeapon != nullptr)
			{
				WeaponSocket = TEXT("spine_03Socket_main");
				MainWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
				MainWeapon->SetActorRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));  //Delete this later!!!!!!!!!!
			}
		}
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
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ABTCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ABTCharacter::StopRun);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ABTCharacter::StartAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ABTCharacter::StopAim);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ABTCharacter::StartAttack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ABTCharacter::StopAttack);
	PlayerInputComponent->BindAction("ToggleWeapon", IE_Pressed, this, &ABTCharacter::ChangeWeapon);
	PlayerInputComponent->BindAction("PutWeapon", IE_Pressed, this, &ABTCharacter::PutWeapon);
	PlayerInputComponent->BindAxis("LookUp", this, &ABTCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ABTCharacter::Turn);
	PlayerInputComponent->BindAxis("UpDown", this, &ABTCharacter::UpDown);
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
void ABTCharacter::StartRun()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed * SpeedMultiplier;
}
void ABTCharacter::StopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed * SpeedMultiplier;
}
void ABTCharacter::StartAim()
{
	LengthTo = AimModeLength;
	LoTo = AimModeLo;
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->MaxWalkSpeed = CrawlSpeed * SpeedMultiplier;
}
void ABTCharacter::StopAim()
{
	LengthTo = NormalModeLength;
	LoTo = NormalModeLo;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed * SpeedMultiplier;
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
	if(CurrentWeapon != nullptr)
		CurrentWeapon->StopAttack();
}