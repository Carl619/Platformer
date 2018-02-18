// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "../Components/LifeComponent.h"
#include "../Components/PunchComponent.h"
#include "../Components/JetComponent.h"
#include "../Components/ShootComponent.h"
#include "../../Props/TreasureBlock.h"
#include "../../Props/BreakableBlock.h"

// Input

APlayerCharacter::APlayerCharacter() {
	JumpHit = CreateDefaultSubobject<USphereComponent>(TEXT("JumpHIt"));
	JumpHit->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBeginJumpCollision);
	JumpHit->SetupAttachment(RootComponent);

	DashDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("DashDirection"));
	DashDirection->SetupAttachment(RootComponent);

	mJet = CreateDefaultSubobject<UJetComponent>(TEXT("JetComponent"));

	mShoot = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Punch", IE_Pressed, this, &APlayerCharacter::Punch);
	PlayerInputComponent->BindAction("Punch", IE_Released, this, &APlayerCharacter::StopPunch);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopUsingJetPack);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCharacter::Shoot);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &APlayerCharacter::Dash);
	PlayerInputComponent->BindAction("JetPack", IE_Pressed, this, &APlayerCharacter::UseJetPack);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
}

void APlayerCharacter::ControlJumping()
{
	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking)
	{
		NumberJumps = 0;
		JumpHit->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}



void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::OnOverlapBeginJumpCollision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != GetOwner()) && (OtherComp != nullptr))
	{
		ABreakableBlock * breakblock = Cast<ABreakableBlock>(OtherActor);
		if (breakblock) {
			breakblock->Destroy();
		}
		else
		{
			ATreasureBlock * treasure = Cast<ATreasureBlock>(OtherActor);
			if (treasure)
			{
				treasure->reward(this);
			}
		}
	}
}

int APlayerCharacter::getAmmo()
{
	return Ammo;
}

int APlayerCharacter::getCoins()
{
	return Coins;
}

bool APlayerCharacter::geUsingJetPack()
{
	return UsingJetPack;
}

UJetComponent * APlayerCharacter::getJet()
{
	return mJet;
}

UShootComponent * APlayerCharacter::getShoot()
{
	return mShoot;
}

void APlayerCharacter::Jump()
{
	if (UsingJetPack && mJet->getFuel()>0)
		mJet->setPropelling(true);
	JumpHit->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	if (NumberJumps < 2) {
		if(NumberJumps==0)
		ACharacter::Jump();
		if (NumberJumps == 1)
			LaunchCharacter(FVector(0,0,ForceSecondJump*GetCharacterMovement()->Mass),false,true);
		NumberJumps++;
	}
}

void APlayerCharacter::Shoot()
{
	if (Ammo > 0) {
		Ammo--;
		mShoot->Shoot();
	}
}

void APlayerCharacter::Dash()
{
	FVector newLocation = FVector(DashDirection->GetForwardVector().X * DashDistance, DashDirection->GetForwardVector().Y * DashDistance, 0);
	newLocation = FVector(newLocation.X + GetActorLocation().X, newLocation.Y + GetActorLocation().Y, GetActorLocation().Z);
	SetActorLocation(newLocation, false, nullptr, ETeleportType::TeleportPhysics);

}

void APlayerCharacter::UseJetPack()
{
	if (UsingJetPack)
		UsingJetPack = false;
	else
		UsingJetPack = true;
}

void APlayerCharacter::StopUsingJetPack()
{
	mJet->setPropelling(false);
}

void APlayerCharacter::Punch()
{

	mPunch->Punch();
}

void APlayerCharacter::StopPunch()
{
	mPunch->StopPunch();
}

void APlayerCharacter::addFuel(float amount)
{
	mJet->addFuel(amount);
}

void APlayerCharacter::addCollectible(int amount)
{
	Coins += amount;
}

void APlayerCharacter::addAmmo(int amount)
{
	Ammo += amount;
}

<<<<<<< HEAD
void APlayerCharacter::slowed(float time)
{
	Slowed = true;
	SlowedTime = time;
	CurrentSlowedTime = 0;
	NormalSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed / 4 * 3;
}
void APlayerCharacter::GetPoisoned(float time,float damage)
{
	mPoisoned = true;
	PoisonTime = time;
	CurrentPoisonTime = 0;
	PoisonDamage = damage;
}

=======
>>>>>>> origin/master
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ControlJumping();
<<<<<<< HEAD
	
	if (mPoisoned) {
		CurrentPoisonTime += DeltaTime;
		if (CurrentPoisonTime > PoisonTime)
		{
			mPoisoned = false;
		}
		else {
			mLife->ContinuousDamageTaken(PoisonDamage);
		}
	}
	if (Slowed) {
		CurrentSlowedTime += DeltaTime;
		if (CurrentSlowedTime > SlowedTime)
		{
			Slowed = false;
			GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
		}
	}
=======
>>>>>>> origin/master
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
