#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CGameMode.generated.h"

UCLASS(minimalapi)
class ACGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACGameMode();

	virtual void BeginPlay() override;
	virtual void EndPlay() override;

public:
	float TotalEnemy
	float DeadEnemy;

	UCGameInstance* GameInstance;

public:
	UFUNCTION(BlueprintNativeEvent)
		void OpenGate();
		void OpenGate_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void SpawnBoss();
		void SpawnBoss_Implementation();
};



