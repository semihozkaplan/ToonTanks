// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(Tank)
    {   
        float DistToTank = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if(DistToTank <= FireRange)
        {
            RotateTurret(Tank->GetActorLocation());
        }
    }

}
