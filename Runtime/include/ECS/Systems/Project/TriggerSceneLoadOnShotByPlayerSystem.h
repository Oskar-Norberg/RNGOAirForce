//
// Created by Oskar.Norberg on 2026-02-20.
//

#pragma once

#include "ECS/Systems/Core/Physics/CollisionSystem.h"
#include "ECS/Systems/ISystem.h"
#include "ECS/Systems/SystemContext.h"
#include "Scene/SceneManager/SceneManager.h"
#include "Scene/World/World.h"

namespace RNGOEngine::Systems::Project
{
    class TriggerSceneLoadOnShotByPlayerSystem : public IGameSystem
    {
    public:
        // TODO: DRY - Copy paste from both imgui and Bullet system
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
                    LoadScene(*context.SceneManager, world, entityA, entityB);
                }
                else if (bIsBullet)
                {
                    LoadScene(*context.SceneManager, world, entityB, entityA);
                }
            }
        }

    private:
        static void LoadScene(
            RNGOEngine::Core::SceneManager& sceneManager, RNGOEngine::Core::World& world,
            const entt::entity bulletEntity, const entt::entity otherEntity
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
            bool otherEntityIsSceneLoader =
                registry.any_of<Components::TriggerSceneLoadOnShotByPlayer>(otherEntity);

            if (!isOwnerPlayer || !otherEntityIsSceneLoader)
            {
                return;
            }

            const auto& sceneLoader = registry.get<Components::SceneTarget>(otherEntity);
            auto scene = std::make_unique<RNGOEngine::Core::Scene>();
            auto yaml =
                YAML::LoadFile(std::string{sceneLoader.SceneNameArr.begin(), sceneLoader.SceneNameArr.end()});
            scene->Deserialize(yaml);
            sceneManager.QueueLoadScene(std::move(scene));
        }
    };
}