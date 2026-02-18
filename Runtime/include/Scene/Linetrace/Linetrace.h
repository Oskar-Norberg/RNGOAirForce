//
// Created by Oskar.Norberg on 2026-02-18.
//

#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

namespace RNGOEngine::Core
{
    struct LinetraceResult
    {
        glm::vec3 HitPosition;
        glm::vec3 HitNormal;
        entt::entity HitEntity;
    };

    struct LinetraceQuery
    {
        // NOTE: Has to be in worldspace.
        glm::vec3 Start;
        glm::vec3 End;
    };
}