#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDamage.generated.h"

USTRUCT()
struct FHitData
{
	GENERATED_BODY()

public:
	//Character에게 입히는 데미지 수치
	UPROPERTY(EditAnywhere, Category = "Damage")
		float Damage = 0.0f;

	//LaunchPercent: 각 축으로 날라가는 Launch 비율
	UPROPERTY(EditAnywhere, Category = "Launch")
		float xLaunchPower = 0.0;

	UPROPERTY(EditAnywhere, Category = "Launch")
		float zLaunchPower = 0.0;

	//Effect: 피격 시 나오는 이펙트
	UPROPERTY(EditAnywhere, Category = "Effect")
		class UFXSystemAsset* Effect = nullptr;

	//EffectScale: 피격 시 나오는 이펙트 크기 비율
	UPROPERTY(EditAnywhere, Category = "Effect")
		FVector EffectScale = FVector(1.0f, 1.0f, 1.0f);

	//Location: 피격 시 나오는 이펙트와 사운드 위치
	UPROPERTY(EditAnywhere, Category = "Effect")
		FVector Location = FVector(0.0f, 0.0f, 0.0f);

	//Sound: 피격 시 나오는 사운드
	UPROPERTY(EditAnywhere, Category = "Sound")
		class USoundWave* Sound = nullptr;

	//Debuffs: 피격 시 적용하는 디버프들
	UPROPERTY(EditAnywhere, Category = "Debuff")
		TArray<EDebuff> Debuffs;

public:
	float xLaunch;
	float yLaunch;
	float zLaunch;
};

UINTERFACE(MinimalAPI)
class UIDamage : public UInterface
{
	GENERATED_BODY()
};

class TOPVIEWPROJECT_API IIDamage
{
	GENERATED_BODY()

public:
	virtual void BaseAttack(AActor* InAttacker, const FHitData& HitData) = 0;
};