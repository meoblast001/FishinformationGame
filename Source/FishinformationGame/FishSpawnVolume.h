#pragma once

#include "CoreMinimal.h"
#include "FishSpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class FISHINFORMATIONGAME_API AFishSpawnVolume : public AActor
{
    GENERATED_BODY()

public:
    AFishSpawnVolume();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "Spawn Volume")
    TArray<FVector> GetSpawnPoints(int Amount) const;

    UPROPERTY(EditDefaultsOnly)
    UBoxComponent* BoxComponent;

private:
    FRandomStream RandomStream;
};
