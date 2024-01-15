#include "Skills/CKnockDown.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Interfaces/IDamage.h"
#include "Player/CPlayer.h"

void ACKnockDown::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACKnockDown::OnComponentBeginOverlap);
}

void ACKnockDown::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckNull(OtherActor);

	if(OtherActor != GetOwner())
	{
		IIDamage* HitActor = Cast<IIDamage>(OtherActor);
		CheckNull(HitActor);

		HitActor->BaseAttack(Owner, FHitData);
	}
}
