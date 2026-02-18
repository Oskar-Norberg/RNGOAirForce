//
// Created by ringo on 2026-01-27.
//

#include "ECS/Systems/Core/Physics/CollisionSystem.h"

#include "ECS/Systems/SystemContext.h"
#include "Math/3D/AABB3D.h"
#include "Math/3D/CollisionChecks.h"
#include "Scene/World/World.h"

namespace RNGOEngine::Systems::Core
{
    void CollisionSystem::Update(RNGOEngine::Core::World& world, EngineSystemContext& context)
    {
        EngineSystem::Update(world, context);
        CollisionList collisions = {};

        SphereToSphereCollisionDetection(world, collisions);
        BoxToBoxCollisionDetection(world, collisions);
        SphereToBoxCollisionDetection(world, collisions);

        // Register collisions for both engine and game systems. This will copy the data, but it's fine for now.
        // TODO: Consider using a shared pointer if this becomes a problem.
        context.EngineResourceMapper->AddTransientResource(CollisionList{collisions}, true);
        context.GameResourceMapper->AddTransientResource(std::move(collisions), true);
    }

    void CollisionSystem::SphereToSphereCollisionDetection(
        RNGOEngine::Core::World& world, CollisionList& collisions
    )
    {
        const auto sphereView = world.GetRegistry().view<Components::Transform, Components::SphereCollider>();

        // Simple O(n^2) for now
        for (const auto& [entityA, transformA, sphereA] : sphereView.each())
        {
            for (const auto& [entityB, transformB, sphereB] : sphereView.each())
            {
                if (entityA >= entityB)
                {
                    continue;
                }

                const auto collisionDataOpt = Math::SphereToSphereCollision(
                    {.Center = transformA.Position, .Radius = sphereA.Radius},
                    {.Center = transformB.Position, .Radius = sphereB.Radius}
                );

                if (collisionDataOpt)
                {
                    EntityCollisionData collisionData = {
                        .EntityA = entityA,
                        .EntityB = entityB,
                        .ContactPoint = collisionDataOpt->ContactPoint,
                        .ContactNormal = collisionDataOpt->ContactNormal,
                        .PenetrationDepth = collisionDataOpt->PenetrationDepth,
                    };
                    collisions.collisions.emplace_back(collisionData);
                }
            }
        }
    }

    void CollisionSystem::BoxToBoxCollisionDetection(
        RNGOEngine::Core::World& world, CollisionList& collisions
    )
    {
        const auto boxView = world.GetRegistry().view<Components::Transform, Components::BoxCollider>();

        // Simple O(n^2) for now
        for (const auto& [entityA, transformA, boxA] : boxView.each())
        {
            for (const auto& [entityB, transformB, boxB] : boxView.each())
            {
                if (entityA >= entityB)
                {
                    continue;
                }

                const auto collisionDataOpt = Math::BoxToBoxCollision(
                    {.Center = transformA.Position, .HalfExtents = boxA.HalfExtents},
                    {.Center = transformB.Position, .HalfExtents = boxB.HalfExtents}
                );

                if (collisionDataOpt)
                {
                    // TODO: Slightly unseemly chunk of code duplication, move into helper function.
                    EntityCollisionData collisionData = {
                        .EntityA = entityA,
                        .EntityB = entityB,
                        .ContactPoint = collisionDataOpt->ContactPoint,
                        .ContactNormal = collisionDataOpt->ContactNormal,
                        .PenetrationDepth = collisionDataOpt->PenetrationDepth,
                    };
                    collisions.collisions.emplace_back(collisionData);
                }
            }
        }
    }

    void CollisionSystem::SphereToBoxCollisionDetection(
        RNGOEngine::Core::World& world, CollisionList& collisions
    )
    {
        const auto boxView = world.GetRegistry().view<Components::Transform, Components::BoxCollider>();
        const auto sphereView = world.GetRegistry().view<Components::Transform, Components::SphereCollider>();

        for (const auto& [boxEntity, boxTransform, boxCollider] : boxView.each())
        {
            for (const auto& [sphereEntity, sphereTransform, sphereCollider] : sphereView.each())
            {
                const auto collisionDataOpt = Math::SphereToBoxCollision(
                    {sphereTransform.Position, sphereCollider.Radius},
                    {boxTransform.Position, boxCollider.HalfExtents}
                );

                if (collisionDataOpt)
                {
                    // TODO: Slightly unseemly chunk of code duplication, move into helper function.
                    EntityCollisionData collisionData = {
                        .EntityA = sphereEntity,
                        .EntityB = boxEntity,
                        .ContactPoint = collisionDataOpt->ContactPoint,
                        .ContactNormal = collisionDataOpt->ContactNormal,
                        .PenetrationDepth = collisionDataOpt->PenetrationDepth,
                    };
                    collisions.collisions.emplace_back(collisionData);
                }
            }
        }
    }
}