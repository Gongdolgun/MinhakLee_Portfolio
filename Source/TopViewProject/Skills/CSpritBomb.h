#pragma once

#include "CoreMinimal.h"
#include "Skills/CSkill.h"
#include "Components/TimelineComponent.h"
#include "CSpritBomb.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACSpritBomb : public ACSkill
{
	GENERATED_BODY()
	
public:	
	ACSpritBomb();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void Timeline_Func(float Output);

	UPROPERTY(EditAnywhere)
		UCurveFloat* Curve;

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACSpiritBomb_Explosion> BP_SpiritBomb_Explosion;

};