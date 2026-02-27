//
// Created by Oskar.Norberg on 2026-02-16.
//

#pragma once

#include "ECS/Systems/Core/Physics/CollisionSystem.h"
#include "ECS/Systems/ISystem.h"
#include "ECS/Systems/SystemContext.h"
#include "Scene/World/World.h"

namespace RNGOEngine::Systems::Project
{
    class BulletDestructionSystem : public IGameSystem
    {
    public:
        void Update(RNGOEngine::Core::World& world, SystemContext& context) override
        {
            Core::CollisionList collisions;
            bool found = context.ResourceMapper->TryGetTransientResource(collisions);

            // No collisions to operate on
            if (!found)
            {
                return;
            }

            for (const auto& collisionData : collisions.collisions)
            {
                const auto entityA = collisionData.EntityA;
                const auto entityB = collisionData.EntityB;

                const auto aIsBullet = world.GetRegistry().any_of<Components::Bullet>(entityA);
                const auto bIsBullet = world.GetRegistry().any_of<Components::Bullet>(entityB);

                // Skip bullet on bullet collisions, even though it sounds badass...
                if (aIsBullet && bIsBullet)
                {
                    continue;
                }

                if (aIsBullet)
                {
                    BulletToNonBulletCollision(world, entityA, entityB, *context.SceneManager);
                }
                else if (bIsBullet)
                {
                    BulletToNonBulletCollision(world, entityB, entityA, *context.SceneManager);
                }
            }
        }

    private:
        static void BulletToNonBulletCollision(
            RNGOEngine::Core::World& world, const entt::entity bulletEntity, const entt::entity otherEntity,
            RNGOEngine::Core::SceneManager& sceneManager
        )
        {
            auto& registry = world.GetRegistry();
            const auto& bullet = registry.get<Components::Bullet>(bulletEntity);
            const auto bulletOwner = static_cast<entt::entity>(bullet.Owner);

            if (otherEntity == bulletOwner)
            {
                return;
            }

            // Check Team Affiliation
            bool isOwnerPlayer = registry.any_of<Components::PlayerTag>(bulletOwner);
            bool isOwnerEnemy = registry.any_of<Components::EnemyTag>(bulletOwner);

            bool isOtherPlayer = registry.any_of<Components::PlayerTag>(otherEntity);
            bool isOtherEnemy = registry.any_of<Components::EnemyTag>(otherEntity);

            if (isOwnerPlayer && isOtherEnemy)
            {
                // TODO: Score count? or some dumb shit?
                world.DestroyEntity(bulletEntity);

                world.DestroyEntity(otherEntity);
            }
            else if (isOwnerEnemy && isOtherPlayer)
            {
                world.DestroyEntity(bulletEntity);

                auto scene = std::make_unique<RNGOEngine::Core::Scene>();
                // TODO: Very hardcoded
                auto yaml = YAML::LoadFile("fumo_spline_gameover.rngoscene");
                scene->Deserialize(yaml);
                sceneManager.QueueLoadScene(std::move(scene));
                world.DestroyEntity(otherEntity);
            }
        }
    };
}