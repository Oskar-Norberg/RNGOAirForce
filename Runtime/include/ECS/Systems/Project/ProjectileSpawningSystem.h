//
// Created by Oskar.Norberg on 2026-02-16.
//

#pragma once

#include "Data/MouseCodes.h"
#include "ECS/Components/Components.h"
#include "ECS/Systems/ISystem.h"
#include "ECS/Systems/SystemContext.h"
#include "InputManager/InputManager.h"
#include "Scene/World/World.h"
#include "entt/entity/entity.hpp"

namespace RNGOEngine::Systems::Project
{
    class ProjectileSpawningSystem : public IGameSystem
    {
    public:
        void Update(RNGOEngine::Core::World& world, SystemContext& context) override
        {
            auto& registry = world.GetRegistry();
            entt::entity playerID{entt::null};
            entt::entity playerCameraID{entt::null};

            const auto playerView = registry.view<Components::PlayerTag>();
            for (const auto& entity : playerView)
            {
                playerID = entity;
            }

            const auto cameraView = registry.view<Components::Camera>();
            for (const auto& entity : cameraView)
            {
                playerCameraID = entity;
            }

            // No player found.
            if (playerCameraID == entt::null || playerID == entt::null)
            {
                return;
            }

            // Malformed PlayerCamera (no transform)
            if (!registry.any_of<Components::Transform>(playerCameraID))
            {
                return;
            }

            const auto& playerCameraTransform = registry.get<Components::Transform>(playerCameraID);

            if (context.InputManager->WasMouseButtonPressedThisFrame(
                    Data::MouseCodes::RNGO_MOUSE_BUTTON_LEFT
                ))
            {
                SpawnProjectile(registry, playerID, playerCameraTransform);
            }
        }

    private:
        static void SpawnProjectile(
            entt::registry& registry, entt::entity firedBy, const Components::Transform& spawnTransform
        )
        {
            Components::Transform rotatedTransform = spawnTransform;
            rotatedTransform.Rotation *= glm::angleAxis(glm::radians(180.0f), glm::vec3(0, 1, 0));

            const auto projectileEntity = registry.create();
            registry.emplace<Components::Transform>(projectileEntity, rotatedTransform);
            registry.emplace<Components::MeshRenderer>(projectileEntity);

            // Don't worry about it (:
            registry.emplace<Components::Bullet>(projectileEntity, static_cast<uint32_t>(firedBy));
            registry.emplace<Components::DestroyAfter>(projectileEntity, 5.0f);
            registry.emplace<Components::BoxCollider>(projectileEntity);
        }
    };
}