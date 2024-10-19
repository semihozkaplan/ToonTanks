// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
    Camera->SetupAttachment(SpringArm);
}


void ATank::BeginPlay()
{
	Super::BeginPlay();
    // Casting is a way to convert one type to another but they should be in the same type hierarchy
    // Cast template function -> Cast<type we would like to cast>(type we are casting)
    PlayerControllerRef = Cast<APlayerController>(GetController());   

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FHitResult HitResult;
    if(PlayerControllerRef)
    {
        PlayerControllerRef->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            true,
            HitResult);
        RotateTurret(HitResult.ImpactPoint);

        // DrawDebugSphere(
        //     GetWorld(),
        //     HitResult.ImpactPoint,
        //     50.f,
        //     12,
        //     FColor::Red,
        //     false,
        //     -1.f
        // );
    }
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    
    PlayerInputComponent->BindAction(TEXT("fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value)
{
    FVector DeltaLocation = FVector::ZeroVector;
    // X-Axis = Value * Speed * Deltatime
    DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    // Yaw = Value * DeltaTime * TurnRate
    DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);
}

