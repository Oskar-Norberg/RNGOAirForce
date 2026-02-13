//
// Created by Oskar.Norberg on 2026-02-13.
//

#pragma once

#include "ECS/Systems/ISystem.h"

namespace RNGOEngine::Systems::Project
{
    class SplineAttachmentSystem : public EngineSystem
    {
    public:
        void Update(RNGOEngine::Core::World& world, EngineSystemContext& context) override
        {
            auto attachmentView =
                world.GetRegistry().view<Components::SplineAttachment, Components::Transform>();
            auto splineView = world.GetRegistry().view<Components::Spline>();

            // TODO: Garbage code, for now just support one spline.
            Components::Spline* selectedSpline = nullptr;
            for (const auto& [entity, spline] : splineView.each())
            {
                selectedSpline = &spline;
            }

            if (selectedSpline == nullptr)
            {
                return;
            }

            if (selectedSpline->Points.empty())
            {
                return;
            }

            for (const auto& [entity, attachment, transform] : attachmentView.each())
            {
                transform.Position = selectedSpline->Points[0];
            }
        }
    };
}