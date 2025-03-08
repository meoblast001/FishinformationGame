#include "GameplayGameMode.h"

#include "FishSpawnVolume.h"

AGameplayGameMode::AGameplayGameMode() :
    RandomStream(FDateTime::Now().GetTicks()),
    SpawnVolume(nullptr)
{
}

void AGameplayGameMode::SetSpawnVolume(const AFishSpawnVolume* SpawnVolume)
{
    this->SpawnVolume = SpawnVolume;
    OnSpawnVolumeSet.Broadcast();
}

void AGameplayGameMode::SpawnNonPlayerFish()
{
    if (SpawnVolume == nullptr)
        return;
    check(NonPlayerFishActorClass != nullptr);

    for (FVector SpawnPoint : SpawnVolume->GetSpawnPoints(NumNonPlayerFish))
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

        FRotator SpawnRotation = FRotator(0, 0, RandomStream.FRand());

        GetWorld()->SpawnActor(NonPlayerFishActorClass, &SpawnPoint, &SpawnRotation, SpawnParameters);
    }
}
