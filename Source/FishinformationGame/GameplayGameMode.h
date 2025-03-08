#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawnVolumeSet);

UCLASS()
class FISHINFORMATIONGAME_API AGameplayGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AGameplayGameMode();

    UFUNCTION(BlueprintCallable, Category = "Game Mode")
    void SetSpawnVolume(const AFishSpawnVolume* SpawnVolume);

protected:
    UPROPERTY(EditDefaultsOnly)
    int NumNonPlayerFish;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<AActor> NonPlayerFishActorClass;

    UPROPERTY(BlueprintAssignable, Category = "Game Mode")
    FOnSpawnVolumeSet OnSpawnVolumeSet;

    UFUNCTION(BlueprintCallable, Category = "Game Mode")
    void SpawnNonPlayerFish();

private:
    FRandomStream RandomStream;
    const AFishSpawnVolume* SpawnVolume;
};
