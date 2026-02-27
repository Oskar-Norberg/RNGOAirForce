//
// Created by Oskar.Norberg on 2026-02-27.
//

#pragma once
#include "ECS/Systems/ISystem.h"
#include "ECS/Systems/SystemContext.h"
#include "Scene/World/World.h"

namespace RNGOEngine::Systems::Project
{
    class RotateSystem : public IGameSystem
    {
    public:
        void Update(RNGOEngine::Core::World& world, SystemContext& context) override
        {
            auto& registry = world.GetRegistry();
            auto rotators = registry.view<Components::RotateY, Components::Transform>();

            for (auto [entity, rotator, transform] : rotators.each())
            {
                const auto rotateSpeed = rotator.RotationSpeed;
                transform.Rotation =
                    glm::rotate(transform.Rotation, rotateSpeed * context.DeltaTime, glm::vec3(0, 1, 0));
            }
        }
    };
}