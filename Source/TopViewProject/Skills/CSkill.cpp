#include "Skills/CSkill.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Interfaces/IDamage.h"
#include "Player/CPlayer.h"

ACSkill::ACSkill()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Collision, "Collision", Root);
}

void ACSkill::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());

	if (!Owner)
	{
		return;
	}
}
