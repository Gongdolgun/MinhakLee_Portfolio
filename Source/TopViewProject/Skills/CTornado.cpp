#include "Skills/CTornado.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Interfaces/IDamage.h"

void ACTornado::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACTornado::OnComponentBeginOverlap);
}

void ACTornado::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor != GetOwner())
	{
		ACEnemy* Enemy = Cast<ACEnemy>(OtherActor);
		IIDamage* HitActor = Cast<IIDamage>(Enemy);

		ACPlayer* OwnerPlayer = Cast<ACPlayer>(GetOwner());
		CheckNull(OwnerPlayer);

		if (!!HitActor)
			HitActors.AddUnique(HitActor);

		if(HitActors.Num() > 0)
		{

			for(auto& Hit : HitActors)
			{
				if (!!Hit)
					Hit->BaseAttack(this, HitData);
			}

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_Hit, FTimerDelegate::CreateLambda([=]()
			{
				for (auto& Hit : HitActors)
				{
					if(!!Hit)
						Hit->BaseAttack(Owner, HitData);
				}

				if(!!CameraShake)
					GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CameraShake, ShakeScale);

			}), 0.5f, true);
		}

	}
		
}
