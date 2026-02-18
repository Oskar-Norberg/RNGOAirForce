//
// Created by Oskar.Norberg on 2026-02-18.
//

#pragma once

#include "Data/KeyCodes.h"
#include "ECS/Systems/Core/Physics/CollisionSystem.h"
#include "ECS/Systems/ISystem.h"
#include "ECS/Systems/SystemContext.h"
#include "Scene/World/World.h"

namespace RNGOEngine::Systems::Project
{
    class RailsShooterCameraSystem : public IGameSystem
    {
    public:
        void Update(RNGOEngine::Core::World& world, SystemContext& context) override
        {
            auto& inputManager = *context.InputManager;

            if (inputManager.WasKeyPressedThisFrame(Data::KeyCodes::RNGO_KEY_ESCAPE))
            {
                inputManager.SetMouseMode(Data::Mouse::MouseMode::Normal);
            }

            if (inputManager.WasMouseButtonPressedThisFrame(Data::MouseCodes::RNGO_MOUSE_BUTTON_1))
            {
                inputManager.SetMouseMode(Data::Mouse::MouseMode::Locked);
            }

            const auto view = world.GetRegistry().view<Components::Camera, Components::Transform>();
            for (const auto [entity, camera, transform] : view.each())
            {
                // TODO: Make Data entries for Forward, Right and Up instead of hardcoding them EVERYWHERE.
                glm::vec3 right = glm::normalize(transform.Rotation * glm::vec3(1.0f, 0.0f, 0.0f));

                const auto mouseDelta = inputManager.GetMouseDelta();
                if (mouseDelta.x != 0.0 || mouseDelta.y != 0.0)
                {
                    float yaw = glm::radians(static_cast<float>(-mouseDelta.x) * CAMERA_SENSITIVITY);
                    float pitch = glm::radians(static_cast<float>(-mouseDelta.y) * CAMERA_SENSITIVITY);

                    glm::quat quatYaw = glm::angleAxis(yaw * context.DeltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
                    glm::quat quatPitch = glm::angleAxis(pitch * context.DeltaTime, glm::normalize(right));

                    transform.Rotation = glm::normalize(quatYaw * quatPitch * transform.Rotation);
                }
            }
        }

    private:
        static constexpr auto CAMERA_SENSITIVITY = 100.0f;
    };
}