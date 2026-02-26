//
// Created by Oskar.Norberg on 2026-02-26.
//

#pragma once

#include "Application/Application.h"

namespace RNGOEngine::Runtime
{
    class RuntimeBuild : public Application
    {
    public:
        explicit RuntimeBuild(const EngineConfig& config);

    public:
        void OnUpdate(float deltaTime) override;
        void OnRender() override;

    private:
        void UpdateEngineSystems(float deltaTime);
        void UpdateGameSystems(float deltaTime);
    };
}