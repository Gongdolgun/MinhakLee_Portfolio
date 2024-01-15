#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPVIEWPROJECT_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class USkillData>> SkillDatas;

	UFUNCTION(BlueprintCallable)
		void UseSkill(int SkillIndex);

public:
	ACharacter* Owner;

public:
	UPROPERTY(VisibleAnywhere)
		class USkillData* curSkillData;
};
