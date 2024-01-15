#include "Notifies/N_SpawnActor.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "Player/CPlayer.h"

FString UN_SpawnActor::GetNotifyName_Implementation() const
{
	return "SpawnActor";
}

void UN_SpawnActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACPlayer* Owner = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(Owner);

	USkillComponent* SkillComponent = CHelpers::GetComponent<USkillComponent>(Owner);
	CheckNull(SkillComponent);

	TSubclassOf<ASkill> SpawnSkill = SkillComponent->curSkillData->SkillActor;

	FActorSpawnParameters param;
	param.Owner = Owner;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector Location = Owner->GetActorLocation() + (Owner->GetActorForwardVector() * Spawn_Distance);

	if(!!SpawnActor)
		Owner->GetWorld()->SpawnActor<AActor>(SpawnActor, FVector(Location.X, Location.Y, (Location.Z - Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight())), UKismetMathLibrary::MakeRotFromX(Owner->GetActorForwardVector()), param);
}
