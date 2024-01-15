#include "Skill/SkillData.h"
#include "Animation/AnimMontage.h"
#include "Global.h"
#include "Skill.h"
#include "Net/UnrealNetwork.h"

void USkillData::Play(ACharacter* InOwner)
{
	ACharacter* character = Cast<ACharacter>(InOwner);

	if (character == nullptr)
		return;

	USkillComponent* skillComponent = CHelpers::GetComponent<USkillComponent>(InOwner);

	if (skillComponent == nullptr)
		return;

	character->PlayAnimMontage(Product.ActionMontage, Product.PlayRate);
}