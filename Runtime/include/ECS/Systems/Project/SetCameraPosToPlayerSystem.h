//
// Created by Oskar.Norberg on 2026-02-16.
//

#pragma once

#include "ECS/Systems/Core/Physics/CollisionSystem.h"
#include "ECS/Systems/ISystem.h"
#include "Scene/World/World.h"

namespace RNGOEngine::Systems::Project
{
    class SetCameraPosToPlayerSystem : public IGameSystem
    {
    public:
        void Update(RNGOEngine::Core::World& world, SystemContext& context) override
        {
            auto& registry = world.GetRegistry();
            entt::entity playerEntity = entt::null;

            const auto playerView = registry.view<Components::PlayerTag>();
            for (const auto player : playerView)
            {
                playerEntity = player;
            }

            if (playerEntity == entt::null)
            {
                return;
            }

            // Player is missing transform
            if (!registry.any_of<Components::Transform>(playerEntity))
            {
                return;
            }

            const auto& playerTransform = registry.get<Components::Transform>(playerEntity);
            const auto cameraView = registry.view<Components::Transform, Components::Camera>();

            for (const auto& [cameraEntity, cameraTransform, camera] : cameraView.each())
            {
                // Could add offset here if needed.
                cameraTransform.Position = playerTransform.Position;
            }
        }
    };
}