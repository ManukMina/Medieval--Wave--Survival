// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Characters/SigilPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/SigilAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PlayerItemAbilityManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameplayTags/SigilGampleyTagsInput.h"
#include "Input/SigilInputComponent.h"
#include "Input/SigilInputConfig.h"


// Sets default values
ASigilPlayerCharacter::ASigilPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	ItemAbilityManagerComponent = CreateDefaultSubobject<UPlayerItemAbilityManager>("ItemAbilityManagerComponent");
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	JumpMaxCount = 2;
}


void ASigilPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	MovementState = EMovementState::Walking;
	
	if(IsValid(AnimLayerClass))
	{
		SetLinkedLayerToDefault();
	}
}

void ASigilPlayerCharacter::UnlockHeavyAttack()
{
	bHeavyUnlocked = true;
}

void ASigilPlayerCharacter::HandlePostStartupDataLoaded(USigilCharacterStartupData* LoadedStartupData)
{
    if (!IsValid(LoadedStartupData)) return;
	LoadedStartupData->GiveStartingItems(ItemAbilityManagerComponent);
}



void ASigilPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(InputConfig);

	const ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	check(LocalPlayer);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputConfig->DefaultMappingContext, 0);
	
	if (USigilInputComponent* SigilInputComponent = CastChecked<USigilInputComponent>(PlayerInputComponent))
	{
		SigilInputComponent->BindNativeAction(InputConfig, SigilGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
		SigilInputComponent->BindNativeAction(InputConfig, SigilGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
		SigilInputComponent->BindAbilityAction(InputConfig, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased);
	}
}

void ASigilPlayerCharacter::SetMovementState(const EMovementState InMovementState)
{
	MovementState = InMovementState;
}

void ASigilPlayerCharacter::OnMovementModeChanged(const EMovementMode PrevMovementMode, const uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	if (!IsValid(SigilAbilitySystemComponent)) return;
	
	
	if (GetCharacterMovement()->IsFalling())
	{ 
		SigilAbilitySystemComponent->AddLooseGameplayTag(SigilGameplayTags::Ability_Movement_Airborne);
		SigilAbilitySystemComponent->RemoveLooseGameplayTag(SigilGameplayTags::Ability_Movement_Grounded);
	}
	else if (GetCharacterMovement()->IsMovingOnGround())
	{
		SigilAbilitySystemComponent->AddLooseGameplayTag(SigilGameplayTags::Ability_Movement_Grounded);
		SigilAbilitySystemComponent->RemoveLooseGameplayTag(SigilGameplayTags::Ability_Movement_Airborne);
		SigilAbilitySystemComponent->RemoveLooseGameplayTag(SigilGameplayTags::Ability_Movement_DoubleJump); 
	}
}

void ASigilPlayerCharacter::SetLinkedLayerToDefault()
{
	GetMesh()->LinkAnimClassLayers(AnimLayerClass);
}


void ASigilPlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2d InputValue = Value.Get<FVector2d>();
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	
	const FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector, InputValue.X);
	ControlRotation.Roll = 0.0f;
	AddMovementInput(ControlRotation.Vector(), InputValue.Y);
}

void ASigilPlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2d InputValue = Value.Get<FVector2d>();
	
	AddControllerYawInput(InputValue.X);
	AddControllerPitchInput(InputValue.Y);
}

void ASigilPlayerCharacter::AbilityInputPressed(const FGameplayTag InputTag)
{
	SigilAbilitySystemComponent->AbilityTagPressed(InputTag);
	
}

void ASigilPlayerCharacter::AbilityInputReleased(const FGameplayTag InputTag)
{
	SigilAbilitySystemComponent->AbilityTagReleased(InputTag);
}

