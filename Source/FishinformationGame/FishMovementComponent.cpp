#include "FishMovementComponent.h"

UFishMovementComponent::UFishMovementComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    MeshComponent = nullptr;
}

void UFishMovementComponent::BeginPlay()
{
    Super::BeginPlay();
    Owner = GetOwner();
}

void UFishMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (MeshComponent != nullptr)
        MeshComponent->SetPhysicsAngularVelocityInRadians(FVector::ZeroVector);
}

void UFishMovementComponent::SetMeshComponent(UMeshComponent* MeshComponent)
{
    this->MeshComponent = MeshComponent;
}

void UFishMovementComponent::Rotate(FVector2D Rotation)
{
    if (MeshComponent == nullptr)
        return;
    FVector2D ScaledRotation = Rotation * RotationSpeed;
    // Pitch as local rotation.
    Owner->AddActorLocalRotation(FRotator(ScaledRotation.Y, 0, 0));      
    // Yaw as world rotation to avoid unintentional roll due to pitch.
    Owner->AddActorWorldRotation(FRotator(0, ScaledRotation.X, 0));
}       

void UFishMovementComponent::MoveForward()
{
    if (MeshComponent == nullptr)
        return;
    const auto WorldSpaceForce = GetOwner()->GetActorTransform().TransformVector(FVector(ForwardSpeed, 0.0, 0.0));
    MeshComponent->AddForce(WorldSpaceForce);
}

