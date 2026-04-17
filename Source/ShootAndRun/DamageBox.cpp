// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageBox.h"
#include "Engine/DamageEvents.h"

// Sets default values
ADamageBox::ADamageBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("BoxComponent"));
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void ADamageBox::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);
	
	GetWorld()->GetTimerManager().SetTimer(PeriodicHandle, this, &ADamageBox::ApplyPeriodicDamage, Cooldown, true);
}

void ADamageBox::ApplyPeriodicDamage_Implementation()
{
	for (AActor* Overlapper : OverlappingActors)
	{
		Overlapper->TakeDamage(Damage, FDamageEvent(), nullptr, this);
	}
}

void ADamageBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OverlappingActors.Add(OtherActor);
	OtherActor->TakeDamage(Damage, FDamageEvent(), nullptr, this);
}


void ADamageBox::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlappingActors.Remove(OtherActor);
}

// Called every frame
void ADamageBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

