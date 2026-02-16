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
            entt::entity playerEntity{entt::null};

            const auto playerView = registry.view<Components::PlayerTag>();
            for (const auto& entity : playerView)
            {
                playerEntity = entity;
            }

            // No player found.
            if (playerEntity == entt::null)
            {
                return;
            }

            // Malformed player (no transform)
            if (!registry.any_of<Components::Transform>(playerEntity))
            {
                return;
            }

            const auto& playerTransform = registry.get<Components::Transform>(playerEntity);

            if (context.InputManager->WasMouseButtonPressedThisFrame(
                    Data::MouseCodes::RNGO_MOUSE_BUTTON_LEFT
                ))
            {
                SpawnProjectile(registry, playerEntity, playerTransform);
            }
        }

    private:
        static void SpawnProjectile(
            entt::registry& registry, entt::entity firedBy, const Components::Transform& spawnTransform
        )
        {
            const auto projectileEntity = registry.create();
            registry.emplace<Components::Transform>(projectileEntity, spawnTransform);
            registry.emplace<Components::MeshRenderer>(projectileEntity);

            // Don't worry about it (:
            registry.emplace<Components::Bullet>(projectileEntity, static_cast<uint32_t>(firedBy));
            registry.emplace<Components::DestroyAfter>(projectileEntity, 5.0f);
            registry.emplace<Components::BoxCollider>(projectileEntity);
        }
    };
}