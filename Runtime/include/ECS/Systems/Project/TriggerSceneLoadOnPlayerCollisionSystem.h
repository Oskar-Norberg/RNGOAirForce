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
    class TriggerSceneLoadOnPlayerCollisionSystem : public IGameSystem
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

                const auto aIsPlayer = world.GetRegistry().any_of<Components::PlayerTag>(entityA);
                const auto aIsSceneLoader =
                    world.GetRegistry().any_of<Components::TriggerSceneLoadOnPlayerCollision>(entityB);

                const bool bIsPlayer = world.GetRegistry().any_of<Components::PlayerTag>(entityB);
                const bool bIsSceneLoader =
                    world.GetRegistry().any_of<Components::TriggerSceneLoadOnPlayerCollision>(entityA);

                if (aIsPlayer && aIsSceneLoader)
                {
                    LoadScene(*context.SceneManager, world, entityB);
                }
                else if (bIsPlayer && bIsSceneLoader)
                {
                    LoadScene(*context.SceneManager, world, entityA);
                }
            }
        }

    private:
        static void LoadScene(
            RNGOEngine::Core::SceneManager& sceneManager, RNGOEngine::Core::World& world,
            const entt::entity sceneLoaderEntity
        )
        {
            auto& registry = world.GetRegistry();

            bool scenLoaderHasSceneTarget = registry.any_of<Components::SceneTarget>(sceneLoaderEntity);
            if (!scenLoaderHasSceneTarget)
            {
                return;
            }

            const auto& sceneLoader = registry.get<Components::SceneTarget>(sceneLoaderEntity);
            auto scene = std::make_unique<RNGOEngine::Core::Scene>();
            auto yaml =
                YAML::LoadFile(std::string{sceneLoader.SceneNameArr.begin(), sceneLoader.SceneNameArr.end()});
            scene->Deserialize(yaml);
            sceneManager.QueueLoadScene(std::move(scene));
        }
    };
}