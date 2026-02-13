//
// Created by Oskar.Norberg on 2026-02-13.
//

#pragma once

#include "ECS/Components/Components.h"
#include "ECS/Systems/ISystem.h"

namespace RNGOEngine::Systems::Project
{
    class SplineMovementSystem : public IGameSystem
    {
    public:
        void Update(RNGOEngine::Core::World& world, SystemContext& context) override
        {
            auto attachmentView = world.GetRegistry().view<Components::SplineAttachment>();

            for (const auto& [entity, attachment] : attachmentView.each())
            {
                attachment.T += attachment.Speed * context.DeltaTime;
                attachment.T = std::max(attachment.T, 0.0f);
                attachment.T = std::min(attachment.T, 1.0f);
            }
        }
    };
}