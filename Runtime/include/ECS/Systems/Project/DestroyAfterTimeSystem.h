//
// Created by Oskar.Norberg on 2026-02-16.
//

#pragma once

#include "ECS/Systems/ISystem.h"
#include "ECS/Systems/SystemContext.h"

namespace RNGOEngine::Systems::Project
{
    class DestroyAfterTimeSystem : public IGameSystem
    {
    public:
        void Update(RNGOEngine::Core::World& world, SystemContext& context) override
        {
            auto& registry = world.GetRegistry();
            auto destroyAfterView = registry.view<Components::DestroyAfter>();

            for (const auto& [entity, destroyAfter] : destroyAfterView.each())
            {
                destroyAfter.RemainingTime -= context.DeltaTime;
                if (destroyAfter.RemainingTime <= 0.0f)
                {
                    registry.destroy(entity);
                }
            }
        }
    };
}