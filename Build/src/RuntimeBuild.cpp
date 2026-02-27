//
// Created by Oskar.Norberg on 2026-02-26.
//

#include "RuntimeBuild.h"

#include <iostream>

#include "Utilities/IO/SimpleFileReader/SimpleFileReader.h"

namespace RNGOEngine::Runtime
{
    RuntimeBuild::RuntimeBuild(const EngineConfig& config)
        : Application(config)
    {
        auto scene = std::make_unique<RNGOEngine::Core::Scene>();

        if (!Utilities::IO::FileExists("fumo_spline_menu.rngoscene"))
        {
            std::cout << "Default Scene not found. Follow troubleshooting step 2" << std::endl;
            int unused;
            std::cin >> unused;
            std::abort();
        }

        auto yaml = YAML::LoadFile("fumo_spline_menu.rngoscene");
        scene->Deserialize(yaml);
        m_sceneManager.LoadScene(std::move(scene));
    }

    void RuntimeBuild::OnUpdate(const float deltaTime)
    {
        Application::OnUpdate(deltaTime);

        UpdateEngineSystems(deltaTime);
        UpdateGameSystems(deltaTime);
    }

    void RuntimeBuild::OnRender()
    {
        Application::OnRender();

        m_rendererAPI->RenderToScreen(m_window->GetWidth(), m_window->GetHeight());
    }

    void RuntimeBuild::UpdateEngineSystems(float deltaTime)
    {
        m_engineSystemContext.DeltaTime = deltaTime;
        m_engineSystemContext.DoRunPhysics = (true);
        m_engineSystems.Update(*m_sceneManager.GetCurrentWorld(), m_engineSystemContext);
    }

    void RuntimeBuild::UpdateGameSystems(float deltaTime)
    {
        m_gameSystemContext.DeltaTime = deltaTime;
        m_gameSystems.Update(*m_sceneManager.GetCurrentWorld(), m_gameSystemContext);
    }
}