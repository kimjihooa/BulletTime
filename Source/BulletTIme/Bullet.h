// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BulletTime.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Bullet.generated.h"

UCLASS()
class BULLETTIME_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
		USphereComponent* Collider;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Atk;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float DamageMultiplier;

};
