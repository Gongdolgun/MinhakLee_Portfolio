#include "Skills/CBoss_Tree.h"
#include "Components/BoxComponent.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Interfaces/IDamage.h"


void ACBoss_Tree::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACBoss_Tree::OnComponentBeginOverlap);
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACBoss_Tree::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckNull(OtherActor);

	if (OtherActor != GetOwner())
	{
		IIDamage* HitActor = Cast<IIDamage>(OtherActor);
		CheckNull(HitActor);

		HitActor->BaseAttack(Owner, HitData);
	}
}

void ACBoss_Tree::Explosion()
{
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
