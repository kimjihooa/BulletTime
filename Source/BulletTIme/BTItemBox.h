// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BulletTime.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BTWeapon.h"
#include "BTCharacter.h"
#include "BTItemBox.generated.h"

UCLASS()
class BULLETTIME_API ABTItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABTItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = Box)
		UBoxComponent* Trigger;
	UPROPERTY(VisibleAnywhere, Category = Box)
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = Box)
		TSubclassOf<class ABTWeapon> WeaponClass;
private:
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
