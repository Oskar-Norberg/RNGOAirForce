//
// Created by Oskar.Norberg on 2026-02-26.
//

#pragma once
#include "ECS/Systems/Core/Physics/CollisionSystem.h"
#include "ECS/Systems/ISystem.h"
#include "ECS/Systems/SystemContext.h"
#include "Scene/SceneManager/SceneManager.h"
#include "Scene/World/World.h"

namespace RNGOEngine::Systems::Project
{
    class PlayerContactGameoverSystem : public IGameSystem
    {
    public:
        void Update(RNGOEngine::Core::World& world, SystemContext& context) override
        {
            Core::CollisionList collisions;
            if (!context.ResourceMapper->TryGetTransientResource(collisions))
            {
                return;
            }

            const auto& registry = context.SceneManager->GetCurrentWorld()->GetRegistry();
            for (const auto& collisionData : collisions.collisions)
            {
                const auto entityA = collisionData.EntityA;
                const auto entityB = collisionData.EntityB;

                const bool entityAIsPlayer = registry.any_of<Components::PlayerTag>(entityA);
                const bool entityBIsPlayer = registry.any_of<Components::PlayerTag>(entityB);

                const bool entityAIsEnemy = registry.any_of<Components::EnemyTag>(entityA);
                const bool entityBIsEnemy = registry.any_of<Components::EnemyTag>(entityB);

                if (entityAIsPlayer && entityBIsEnemy)
                {
                    GameOver(*context.SceneManager);
                }
                else if (entityBIsPlayer && entityAIsEnemy)
                {
                    GameOver(*context.SceneManager);
                }
            }
        }

        void GameOver(RNGOEngine::Core::SceneManager& sceneManager)
        {
            // TODO: Hardcoded and not very dry
            auto scene = std::make_unique<RNGOEngine::Core::Scene>();
            auto yaml = YAML::LoadFile("fumo_spline_gameover.rngoscene");
            scene->Deserialize(yaml);
            sceneManager.QueueLoadScene(std::move(scene));
        }
    };

}