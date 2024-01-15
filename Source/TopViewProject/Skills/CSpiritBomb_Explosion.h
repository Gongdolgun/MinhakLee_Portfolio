#pragma once

#include "CoreMinimal.h"
#include "Skills/CSkill.h"
#include "CSpiritBomb_Explosion.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACSpiritBomb_Explosion : public ACSkill
{
	GENERATED_BODY()
	
public:	
	ACSpiritBomb_Explosion();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
		UTimelineComponent* Timeline;

	UPROPERTY(EditAnywhere)
		UCurveFloat* Curve;

public:
	UFUNCTION()
		void Timeline_Func(float Output);

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
