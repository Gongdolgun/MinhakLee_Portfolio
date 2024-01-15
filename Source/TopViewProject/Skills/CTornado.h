#pragma once

#include "CoreMinimal.h"
#include "Skills/CSkill.h"
#include "CTornado.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACTornado : public ACSkill
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	TArray<IIDamage*> HitActors;
	FTimerHandle TimerHandle_Hit;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
