#include "Skills/CBlastFormation.h"
#include "Global.h"
#include "Enemy/CEnemy.h"

void ACBlastFormation::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACBlastFormation::OnComponentBeginOverlap);
}

void ACBlastFormation::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACBlastFormation::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IIDamage* HitActor = Cast<IIDamage>(OtherActor);

	if(!!HitActor && OtherActor!= GetOwner())
	{
		HitActor->BaseAttack(Owner, HitData);
	}
}