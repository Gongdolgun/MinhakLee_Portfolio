#pragma once

#include "CoreMinimal.h"
#include "Skills/CSkill.h"
#include "CKnockDown.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACKnockDown : public ACSkill
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
