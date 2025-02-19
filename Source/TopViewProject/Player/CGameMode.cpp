#include "CGameMode.h"
#include "CPlayerController.h"
#include "CPlayer.h"
#include "UObject/ConstructorHelpers.h"

ACGameMode::ACGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ACPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ACGameMode::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UCGameInstance>(GetGameInstance());
	DeadEnemy = GameInstance->DeadEnemy;
}

void ACGameMode::EndPlay()
{
	Super::EndPlay();

	GameInstance->DeadEnemy = DeadEnemy;
}

void ACGameMode::OpenGate_Implementation()
{

}

void ACGameMode::SpawnBoss_Implementation()
{

}