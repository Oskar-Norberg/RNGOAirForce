//
// Created by Oskar.Norberg on 2025-08-25.
//

#include "Assets/Asset.h"
#include "RuntimeBuild.h"

int main()
{
    using enum RNGOEngine::AssetHandling::AssetType;

    constexpr RNGOEngine::EngineConfig config{RNGOEngine::RenderType::GLFW_OpenGL,
                                              RNGOEngine::PipelineType::Forward,
                                              1280,
                                              720,
                                              "RNGOAirForce",
                                              {},
                                              true};

    RNGOEngine::Runtime::RuntimeBuild runtime(config);
    runtime.Run();

    return 0;
}