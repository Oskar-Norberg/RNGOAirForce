//
// Created by Oskar.Norberg on 2026-02-18.
//

#pragma once

#include <optional>

#include "glm/vec3.hpp"

namespace RNGOEngine::Math
{
    struct CollisionData
    {
        glm::vec3 ContactPoint;
        glm::vec3 ContactNormal;
        float PenetrationDepth;
    };

    struct SphereData
    {
        glm::vec3 Center;
        float Radius;
    };

    struct BoxData
    {
        glm::vec3 Center;
        glm::vec3 HalfExtents;
    };

    std::optional<CollisionData> SphereToSphereCollision(
        const SphereData& sphereA, const SphereData& sphereB
    );
    std::optional<CollisionData> BoxToBoxCollision(const BoxData& boxA, const BoxData& boxB);
    std::optional<CollisionData> SphereToBoxCollision(const SphereData& sphere, const BoxData& box);

}