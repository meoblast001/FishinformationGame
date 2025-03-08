#include "FishSpawnVolume.h"

#include "GameplayGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


AFishSpawnVolume::AFishSpawnVolume() :
    BoxComponent(CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"))),
    RandomStream(FDateTime::Now().GetTicks())
{
    RootComponent = BoxComponent;
}

void AFishSpawnVolume::BeginPlay()
{
    Super::BeginPlay();
    AGameplayGameMode* GameMode = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    GameMode->SetSpawnVolume(this);
}

TArray<FVector> AFishSpawnVolume::GetSpawnPoints(int Amount) const
{
    TArray<FVector> SpawnPointsOut;
    for (int i = 0; i < Amount; ++i)
    {
        SpawnPointsOut.Add(RandomStream.RandPointInBox(BoxComponent->Bounds.GetBox()));
    }
    return SpawnPointsOut;
}
