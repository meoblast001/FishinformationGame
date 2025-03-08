// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FishMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FISHINFORMATIONGAME_API UFishMovementComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFishMovementComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void SetMeshComponent(UMeshComponent* MeshComponent);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Rotate(FVector2D Rotation);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void MoveForward();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ForwardSpeed;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RotationSpeed;

private:
    AActor* Owner;
    UMeshComponent* MeshComponent;
};
