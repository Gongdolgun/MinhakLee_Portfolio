#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillData.generated.h"

UCLASS(Blueprintable, BlueprintType)
class TOPVIEWPROJECT_API USkillData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* ActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACSkill> SkillActor;

	UPROPERTY(EditAnywhere)
		FVector RelativeLocation = FVector::ZeroVector;

public:
	UFUNCTION()
	virtual void Play(ACharacter* InOwner);
	
};