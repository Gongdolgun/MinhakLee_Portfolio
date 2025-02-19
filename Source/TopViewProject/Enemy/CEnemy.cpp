#include "Enemy/CEnemy.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Global.h"
#include "Camera/CameraComponent.h"
#include "Components/CAIBehaviorComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CWeaponComponent_Enemy.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/CPlayer.h"
#include "Weapon/CWeapon_Enemy.h"
#include "Widgets/CUserWidget_HPBar.h"
#include "Widgets/CUserWidget_Damage.h"
#include "CChaosController.h"
#include "GameInstance_Test.h"
#include "Widgets/CUserWidget_Chaos.h"

ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UWidgetComponent>(this, &WDG_HPBar, "HPBar", GetCapsuleComponent());
	CHelpers::CreateComponent<UWidgetComponent>(this, &WDG_Damage, "Damage", GetCapsuleComponent());
	CHelpers::CreateActorComponent<UTimelineComponent>(this, &Timeline, "Timeline");
	CHelpers::CreateActorComponent<UCAIBehaviorComponent>(this, &Behavior, "Behavior");
	CHelpers::CreateActorComponent<UCWeaponComponent_Enemy>(this, &WeaponComponent, "Weapon");

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	WDG_HPBar->SetHiddenInGame(true);

	maxDamage = 1000.f;
	minDamage = maxDamage * 0.7f;
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	target = CHelpers::FindActor<ACPlayer>(GetWorld());

	HP = Max_HP;
	
	FOnTimelineFloat timeline;
	timeline.BindUFunction(this, "Appearance");

	CheckNull(Curve);
	Timeline->AddInterpFloat(Curve, timeline);
	Timeline->SetLooping(false);
	Timeline->SetPlayRate(1.f);
	Timeline->ReverseFromEnd();

	GameMode = Cast<UCGameMode>(GetWorld()->GetGameMode());
}

void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsDead == true)
	{
		GetMovementComponent()->Velocity = FVector::ZeroVector;
	}
}


void ACEnemy::BaseAttack(AActor* InAttacker, const FHitData& HitData)
{
	IIDamage::BaseAttack(InAttackType, Attacker, PlayRate, Damage, LaunchRate);
	AActor* Attacker = Cast<AActor>(InAttacker);

	CheckNull(Attacker);
	CheckTrue(IsDead);

	isHitted = true;
	Behavior->SetTarget(Attacker);

	Behavior->SetHittedMode();
	GetCapsuleComponent()->SetCollisionProfileName("HittedProfile");

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), GetActorLocation());

	FRotator LookAt;
	LookAt = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Attacker->GetActorLocation());

	SetActorRotation(FRotator(0, LookAt.Yaw, 0));
	FVector launch = FVector(InHitData.xLaunchPower * direction.X, InHitData.xLaunchPower * direction.Y, InHitData.zLaunchPower);
	LaunchCharacter(launch, false, false);

	PlayAnimMontage(HitData->ActionMontage, HitData->PlayRate);

	////////////////////// Set Damage

	{
		HP = UKismetMathLibrary::Clamp(HP - Damage, 0, Max_HP);
		WDG_HPBar->SetHiddenInGame(false);
		

		UCUserWidget_HPBar* hpBar = Cast<UCUserWidget_HPBar>(WDG_HPBar->GetUserWidgetObject());
		CheckNull(hpBar);

		hpBar->HPBar->SetPercent(HP / Max_HP);

		if(HP == 0)
		{
			IsDead = true;

			if (!!GameMode)
				++GameMode->DeadEnemy;

			DoRagDoll();
			WDG_HPBar->SetHiddenInGame(true);

			FTimerHandle T_Disappear;
			GetWorld()->GetTimerManager().SetTimer(T_Disappear, FTimerDelegate::CreateLambda([&]()
			{
				Timeline->PlayFromStart();
				GetWorld()->GetTimerManager().ClearTimer(T_Disappear);
			}), 2.f, false);

			FTimerHandle timer;
			GetWorld()->GetTimerManager().SetTimer(timer, FTimerDelegate::CreateLambda([&]()
			{
				WeaponComponent->Weapon->Destroy();

				Destroy();
			}), 3.f, false);
		}
	}

	// Set Damage Widget
	{
		CheckNull(WDG_Damage->GetWidget());

		UCUserWidget_Damage* userwidget_Damage;
		userwidget_Damage = Cast<UCUserWidget_Damage>(WDG_Damage->GetWidget());
		
		FString damage;
		damage = FString::FormatAsNumber(Damage);

		userwidget_Damage->changeText(damage, Player->bCritical);
	}
}

void ACEnemy::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	//GetCapsuleComponent()->SetCollisionProfileName("Pawn");
}

void ACEnemy::Appearance(float Output)
{
	GetMesh()->SetScalarParameterValueOnMaterials("Appearance", Output);
}

void ACEnemy::DoRagDoll()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetMesh()->SetSimulatePhysics(true);

	FVector ImpulseDirection = GetActorRotation().Vector() * -1.0f;
	ImpulseDirection.Normalize();

	//�浹 ����
	float ImpulseStrength = 5000.0f;

	FVector FinalImpulse = ImpulseDirection * ImpulseStrength;

	//GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);
	GetMesh()->AddImpulseToAllBodiesBelow(FinalImpulse, NAME_None);
}

float ACEnemy::Cal_Damage(float percent)
{
	FinalDamage = UKismetMathLibrary::RandomFloatInRange(minDamage, maxDamage);

	return FinalDamage * (percent * 0.01f);;
}
