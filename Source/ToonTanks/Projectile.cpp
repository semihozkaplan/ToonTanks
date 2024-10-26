// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	SetRootComponent(ProjectileMesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovement->InitialSpeed = 800.f;
	ProjectileMovement->MaxSpeed = 800.f;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Adding a delegate to the OnHit event
	// In this way, our function OnHit will be added in InvocationList of OnHit event to be called when the event is broadcasted.
	// This is also usage of multi-cast delegate
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile Hit Event"));
	UE_LOG(LogTemp, Warning, TEXT("Hit Component: %s"), *HitComp->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name: %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Hit Actor Comp Name: %s"), *OtherComp->GetName());
}

