//
// Created by Oskar.Norberg on 2026-02-18.
//

#include "Math/3D/CollisionChecks.h"

#include "Math/3D/AABB3D.h"
#include "glm/geometric.hpp"

namespace RNGOEngine::Math
{
    std::optional<CollisionData> SphereToSphereCollision(const SphereData& sphereA, const SphereData& sphereB)
    {
        if (glm::length(sphereA.Center - sphereB.Center) <= sphereA.Radius + sphereB.Radius)
        {
            const auto contactPoint = (sphereA.Center + sphereB.Center) / 2.0f;
            const auto contactNormal = glm::normalize(sphereB.Center - sphereA.Center);
            const auto penetrationDepth =
                (sphereA.Radius + sphereB.Radius) - glm::length(sphereA.Center - sphereB.Center);

            return CollisionData{
                .ContactPoint = contactPoint,
                .ContactNormal = contactNormal,
                .PenetrationDepth = penetrationDepth,
            };
        }

        return std::nullopt;
    }

    std::optional<CollisionData> BoxToBoxCollision(const BoxData& boxA, const BoxData& boxB)
    {
        const glm::vec3 minA = boxA.Center - boxA.HalfExtents;
        const glm::vec3 maxA = boxA.Center + boxA.HalfExtents;
        const glm::vec3 minB = boxB.Center - boxB.HalfExtents;
        const glm::vec3 maxB = boxB.Center + boxB.HalfExtents;

        const AABB3D<float> aabbA{{minA.x, minA.y, minA.z}, {maxA.x, maxA.y, maxA.z}};
        const AABB3D<float> aabbB{{minB.x, minB.y, minB.z}, {maxB.x, maxB.y, maxB.z}};

        if (aabbA.Intersects(aabbB))
        {
            const auto contactPoint = (boxA.Center + boxB.Center) / 2.0f;
            const auto contactNormal = glm::normalize(boxB.Center - boxA.Center);
            const auto penetrationDepth = glm::length(glm::min(maxA, maxB) - glm::max(minA, minB));

            return CollisionData{
                .ContactPoint = contactPoint,
                .ContactNormal = contactNormal,
                .PenetrationDepth = penetrationDepth,
            };
        }

        return std::nullopt;
    }

    std::optional<CollisionData> SphereToBoxCollision(const SphereData& sphere, const BoxData& box)
    {
        const glm::vec3 boxMin = box.Center - box.HalfExtents;
        const glm::vec3 boxMax = box.Center + box.HalfExtents;

        const glm::vec3 closestPoint = glm::clamp(sphere.Center, boxMin, boxMax);

        const float distanceSquared = glm::dot(closestPoint - sphere.Center, closestPoint - sphere.Center);

        if (distanceSquared <= sphere.Radius * sphere.Radius)
        {
            const auto contactPoint = closestPoint;
            const auto contactNormal = glm::normalize(sphere.Center - closestPoint);
            const auto penetrationDepth = sphere.Radius - glm::sqrt(distanceSquared);

            return CollisionData{
                .ContactPoint = contactPoint,
                .ContactNormal = contactNormal,
                .PenetrationDepth = penetrationDepth,
            };
        }

        return std::nullopt;
    }
}