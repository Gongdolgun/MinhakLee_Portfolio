#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDamage.generated.h"

USTRUCT()
struct FHitData
{
	GENERATED_BODY()

public:
	//Character���� ������ ������ ��ġ
	UPROPERTY(EditAnywhere, Category = "Damage")
		float Damage = 0.0f;

	//LaunchPercent: �� ������ ���󰡴� Launch ����
	UPROPERTY(EditAnywhere, Category = "Launch")
		float xLaunchPower = 0.0;

	UPROPERTY(EditAnywhere, Category = "Launch")
		float zLaunchPower = 0.0;

	//Effect: �ǰ� �� ������ ����Ʈ
	UPROPERTY(EditAnywhere, Category = "Effect")
		class UFXSystemAsset* Effect = nullptr;

	//EffectScale: �ǰ� �� ������ ����Ʈ ũ�� ����
	UPROPERTY(EditAnywhere, Category = "Effect")
		FVector EffectScale = FVector(1.0f, 1.0f, 1.0f);

	//Location: �ǰ� �� ������ ����Ʈ�� ���� ��ġ
	UPROPERTY(EditAnywhere, Category = "Effect")
		FVector Location = FVector(0.0f, 0.0f, 0.0f);

	//Sound: �ǰ� �� ������ ����
	UPROPERTY(EditAnywhere, Category = "Sound")
		class USoundWave* Sound = nullptr;

	//Debuffs: �ǰ� �� �����ϴ� �������
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