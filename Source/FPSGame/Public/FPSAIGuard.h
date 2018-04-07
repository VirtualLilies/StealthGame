// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

// Creating an enum (needs to be uint8 since we expose this to blueprints otherwise there's no need to define the enum as uint8)
UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,

	Suspicious,

	Alerted

};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* HeardPawn, const FVector& Location, float Volume);

	FRotator OriginalRotation;

	UFUNCTION()
	void ResetOrientation();

	FTimerHandle TimerHandle_ResetOrientation;

	EAIState GuardState;

	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChanged(EAIState NewState);

	// CHALLENGE CODE

	/* Let the guard go on patrol */
	UPROPERTY(EditInstanceOnly, Category = "AI")
	bool bPatrol;

	/* First of two patrol points to patrol between */
	// What meta does is simply stating that if bPatrol is true then a variable is editable, if bPatrol was false, then the variable would be grayed out in the instance of the actor
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
	AActor* FirstPatrolPoint;

	/* Second of two patrol points to patrol between */
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
	AActor* SecondPatrolPoint;

	// The current point the actor is either moving to or standing at
	AActor* CurrentPatrolPoint;

	void MoveToNextPatrolPoint();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
	
};
