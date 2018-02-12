// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseThirdPersonCharacter.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.generated.h"

class UJetComponent;
class UShootComponent;
/**
 * 
 */
UCLASS()
class PLATFORMER_API APlayerCharacter : public ABaseThirdPersonCharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		USphereComponent * JumpHit;
	UPROPERTY(EditAnywhere)
		UArrowComponent* DashDirection;

	APlayerCharacter();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	UFUNCTION()
		void OnOverlapBeginJumpCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
		int getAmmo();
	UFUNCTION(BlueprintCallable)
		int getCoins();
	UFUNCTION(BlueprintCallable)
		bool geUsingJetPack();
	UFUNCTION(BlueprintCallable)
		UJetComponent* getJet();
	UFUNCTION(BlueprintCallable)
		UShootComponent* getShoot();
	void Jump();
	void Shoot();
	void Dash();
	void UseJetPack();
	void StopUsingJetPack();
	void Punch();
	void StopPunch();
	void addFuel(float amount);
	void addCollectible(int amount);
	void addAmmo(int amount);
	virtual void Tick(float DeltaTime) override;
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	
private:

	void ControlJumping();
	/*The impulse that will receive the actor to be propelled*/
	UPROPERTY(EditAnywhere, Category = "Platformer")
		int Ammo = 100;
	UPROPERTY(EditAnywhere, Category = "Platformer")
		float DashDistance = 100;
	UPROPERTY(EditAnywhere, Category = "Platformer")
		int Coins = 0;
	UPROPERTY(EditAnywhere, Category = "Platformer")
		float Speed = 100;
	UPROPERTY(EditAnywhere, Category = "Platformer")
		float ForceSecondJump = 10;
	UPROPERTY(EditAnywhere, Category = "Platformer")
		bool UsingJetPack = false;
	UPROPERTY(EditAnywhere, Category = "Platformer")
		bool Propelling = false;
	UPROPERTY(EditAnywhere, Category = "Platformer")
		int NumberJumps = 0;
	UPROPERTY(EditAnywhere, Category = "Platformer")
		int MaxNumberJumps = 2;
	UPROPERTY(EditAnywhere, Category = "Platformer")
		UJetComponent * mJet;
	UPROPERTY(EditAnywhere, Category = "Platformer")
	UShootComponent*mShoot;
};
