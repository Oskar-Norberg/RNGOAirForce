//
// Created by Oskar.Norberg on 2025-08-26.
//

#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Assets/Asset.h"

namespace RNGOEngine::Components
{
    // TODO: Implement a custom FixedString templated-type?
    constexpr auto MAX_NR_CHARACTERS = 24 + 1;
    constexpr auto UNNAMED_ENTITY = "Unnamed Entity";
    struct Name
    {
        std::array<char, MAX_NR_CHARACTERS> NameArr;
    };

    struct Transform
    {
        glm::vec3 Position = {0.0f, 0.0f, 0.0f};
        glm::quat Rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        glm::vec3 Scale = {1.0f, 1.0f, 1.0f};

        // TODO: Profile this versus just storing the matrix directly.
        // TODO: Give more descriptive name. Is this a ModelMatrix? A ViewMatrix? Does it take parenting into account?
        glm::mat4 GetMatrix() const
        {
            auto m = glm::mat4(1.0f);
            m = glm::translate(m, Position);
            m *= glm::toMat4(Rotation);
            m = glm::scale(m, Scale);

            return m;
        }
    };

    struct MeshRenderer
    {
        AssetHandling::ModelHandle ModelHandle;
        AssetHandling::MaterialHandle MaterialKey;
    };

    struct Camera
    {
        float FOV = 45.0f;
        float NearPlane = 0.1f;
        float FarPlane = 100.0f;
    };

    struct SphereCollider
    {
        float Radius = 1.0f;
    };

    struct BoxCollider
    {
        glm::vec3 HalfExtents = glm::vec3(0.5f, 0.5f, 0.5f);
    };

    struct Rigidbody
    {
        bool IsKinematic = false;
        glm::vec3 LinearVelocity = glm::vec3{0.0f};
        bool HasGravity = true;
    };

    struct Color
    {
        glm::vec3 ColorValue = glm::vec3(1.0f, 1.0f, 1.0f);
    };

    struct Intensity
    {
        float IntensityValue = 1.0f;
    };

    struct BackgroundColor
    {
    };

    struct LightFalloff
    {
        // Standard range is 100
        // https://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
        float Constant = 1.0f;
        float Linear = 0.045f;
        float Quadratic = 0.0075f;
    };

    struct AmbientLight
    {
    };

    struct DirectionalLight
    {
    };

    struct PointLight
    {
    };

    struct Spotlight
    {
        float CutOff = glm::cos(glm::radians(10.0f));
        float OuterCutOff = glm::cos(glm::radians(12.5f));
    };

    // Project Specific Components
    struct Spline
    {
        struct SplinePoint
        {
            glm::vec3 Position = glm::vec3{0.0f};
            glm::quat Rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        };
        std::vector<SplinePoint> Points;

        std::pair<glm::vec3, glm::quat> GetTransformAtT(const float t) const
        {
            if (Points.size() == 1)
            {
                return std::make_pair(Points[0].Position, Points[0].Rotation);
            }

            const float clampedT = glm::clamp(t, 0.0f, 1.0f);
            const auto totalLength = static_cast<float>(Points.size() - 1);
            const float scaledT = clampedT * totalLength;
            const size_t indexA = glm::floor(scaledT);
            const size_t indexB = glm::min(indexA + 1, Points.size() - 1);
            const float localT = scaledT - static_cast<float>(indexA);

            const auto mixVec = glm::mix(Points[indexA].Position, Points[indexB].Position, localT);
            const auto mixQuat = glm::slerp(Points[indexA].Rotation, Points[indexB].Rotation, localT);
            return std::make_pair(mixVec, mixQuat);
        }
    };

    struct SplineAttachment
    {
        // How far along the spline the entity is. Range [0, 1].
        float T = 0.0f;
        // How many % of the spline should be covered per second.
        float Speed = 0.01f;
    };

    struct PlayerTag
    {
    };

    struct EnemyTag
    {
    };

    struct Bullet
    {
        // Don't ask me why this is storing a uint32_t instead of an entt::entity. Just don't worry about it.
        std::uint32_t Owner;
        float Speed = 10.0f;
    };

    struct DestroyAfter
    {
        // Seconds
        float RemainingTime = 0.0f;
    };
}
