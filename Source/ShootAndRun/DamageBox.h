// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "DamageBox.generated.h"

UCLASS()
class SHOOTANDRUN_API ADamageBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageBox();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DamageBox")
	UBoxComponent* BoxComponent = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DamageBox")
	float Damage = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DamageBox")
	float Cooldown = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DamageBox")
	float Lifetime = 10.f;

	TArray<AActor*> OverlappingActors;

	FTimerHandle PeriodicHandle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void ApplyPeriodicDamage();
	void ApplyPeriodicDamage_Implementation();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,	bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
