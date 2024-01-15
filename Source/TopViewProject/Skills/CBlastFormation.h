#pragma once

#include "CoreMinimal.h"
#include "Skills/CSkill.h"
#include "CBlastFormation.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACBlastFormation : public ACSkill
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere)
	float DamagePercent = 500.f;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	TArray<UActorComponent*> Collisions;
	float time = 0;
};
