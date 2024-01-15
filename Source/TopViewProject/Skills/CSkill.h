#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IDamage.h"
#include "CKnockDown.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACSkill : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSkill();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* Collision;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UMatineeCameraShake> CameraShake;

	UPROPERTY(EditAnywhere, Category = "CameraShake")
		float CS_Scale;

	UPROPERTY(EditAnywhere, Category = "Hit Data")
		FHitData HitData;

protected:
	class ACharacter* Owner;
};
