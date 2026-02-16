//
// Created by Oskar.Norberg on 2026-02-16.
//

#pragma once

#include "ECS/Systems/ISystem.h"
#include "ECS/Systems/SystemContext.h"
#include "Scene/World/World.h"

namespace RNGOEngine::Systems::Project
{
    class BulletMovementSystem : public IGameSystem
    {
    public:
        void Update(RNGOEngine::Core::World& world, SystemContext& context) override
        {
            auto& registry = world.GetRegistry();
            auto view = registry.view<Components::Transform, Components::Bullet>();

            for (const auto& [entity, transform, bullet] : view.each())
            {
                const auto forward = transform.Rotation * glm::vec3(0.0f, 0.0f, 1.0f);
                transform.Position += forward * bullet.Speed * context.DeltaTime;
            }
        }
    };
}