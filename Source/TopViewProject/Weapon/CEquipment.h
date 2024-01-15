#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Weapons/CWeaponStructures.h"
#include "CEquipment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentEquip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentBeginEquip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentUnequip);

UCLASS(Blueprintable)
class TOPVIEWPROJECT_API UCEquipment : public UObject
{
	GENERATED_BODY()
	
public:
	FORCEINLINE bool GetBeginEquip() { return bBeginEquip; }
	FORCEINLINE const bool* GetEquipped() { return &bEquipped; }

public:
	void BeginPlay(class ACharacter* InOwner, const FEquipmentData& InData);

public:
	void Equip();	
	void Begin_Equip();
	void End_Equip();
	void UnEquip();

public:
	FEquipmentBeginEquip OnEquipmentEquip;
	FEquipmentBeginEquip OnEquipmentBeginEquip;
	FEquipmentUnequip OnEquipmentUnequip;

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;
	
private:
	FEquipmentData Data;

private:
	class UCMovementComponent* Movement;
	class UCStateComponent* State;

private:
	bool bBeginEquip;
	bool bEquipped;
};
