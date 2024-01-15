#include "Skills/CSpritBomb.h"
#include "Skills/CSpiritBomb_Explosion.h"
#include "Global.h"
#include "NiagaraFunctionLibrary.h"


void ACSpritBomb::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACSpritBomb::OnComponentBeginOverlap);

	if(!!Curve)
	{
		FOnTimelineFloat timeline;
		timeline.BindUFunction(this, "Timeline_Func");
		Timeline->AddInterpFloat(Curve, timeline);
		Timeline->SetLooping(false);
		Timeline->SetPlayRate(0.2);
	}

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
	TEnumAsByte<EObjectTypeQuery> WorldDynamic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic);
	ObjectTypes.Add(WorldStatic);
	ObjectTypes.Add(WorldDynamic);

	TArray<AActor*> ignores;
	ignores.Add(GetOwner());

	FHitResult hitResult;
	UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), GetActorLocation(), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().X - 1000.f), ObjectTypes, false, ignores, EDrawDebugTrace::None, hitResult, true);

	if (!!hitResult.bBlockingHit)
	{
		CheckNull(Ground_Effect);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Ground_Effect, hitResult.Location);
	}

	Timeline->PlayFromStart();
}

void ACSpritBomb::Timeline_Func(float Output)
{
	SetActorScale3D(UKismetMathLibrary::VInterpTo(FVector::ZeroVector, FVector(1.6, 1.6, 1.6), Output));
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CS_Base, CS_Scale);
}

void ACSpritBomb::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FActorSpawnParameters param;
	param.Owner = GetOwner();
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (OtherActor != GetOwner())
	{
		GetWorld()->SpawnActor<ACSpiritBomb_Explosion>(BP_SpiritBomb_Explosion, GetActorLocation(), FRotator::ZeroRotator, param);
		Destroy();
	}
}
