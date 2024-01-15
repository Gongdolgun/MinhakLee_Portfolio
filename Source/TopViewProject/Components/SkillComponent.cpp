#include "Components/SkillComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Skill/SkillData.h"
#include "Skill/Skill.h"
#include "Skill/SkillDatas/SkillData_Projectile.h"
#include "Global.h"

USkillComponent::USkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());

	
}


void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void USkillComponent::UseSkill(int SkillIndex)
{
	if (SkillData != nullptr)
	{
		curSkillData = NewObject<USkillData>(Owner, SkillDatas[SkillIndex]);

		if (curSkillData == nullptr)
			curSkillData = SkillData;

		curSkillData->Play(Owner);
	}
}