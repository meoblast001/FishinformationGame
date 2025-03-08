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
    {
        MeshComponent->SetPhysicsAngularVelocityInRadians(FVector::ZeroVector);

        // If velocity exceeds maximum velocity, create an inverted vector of the excess velocity vector and apply it
        // as an impulse to counteract it (i.e. capping velocity at max velocity).
        FVector Velocity = MeshComponent->GetPhysicsLinearVelocity();
        double VelocityMagnitude = Velocity.Size();
        if (VelocityMagnitude > MaximumVelocity)
        {
            FVector OutOfBoundsVelocity = Velocity - Velocity.GetSafeNormal() * MaximumVelocity;
            MeshComponent->AddImpulse(-OutOfBoundsVelocity * MeshComponent->GetMass());
        }
    }
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
    FVector WorldSpaceForce = Owner->GetActorTransform().TransformVector(FVector(ForwardSpeed, 0.0, 0.0));
    MeshComponent->AddForce(WorldSpaceForce);
}
