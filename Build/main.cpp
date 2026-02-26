//
// Created by Oskar.Norberg on 2025-08-25.
//

#include "Assets/Asset.h"
#include "RuntimeBuild.h"

int main()
{
    using enum RNGOEngine::AssetHandling::AssetType;

    static const std::filesystem::path assetPaths[] = {
        EDITOR_ASSETS_DIR, EDITOR_TEXTURES_DIR, EDITOR_SHADERS_DIR, EDITOR_MODELS_DIR
    };
    constexpr RNGOEngine::EngineConfig config{
        RNGOEngine::RenderType::GLFW_OpenGL,
        RNGOEngine::PipelineType::Forward,
        1280,
        720,
        "RNGOAirForce",
        assetPaths,
        true
    };

    RNGOEngine::Runtime::RuntimeBuild runtime(config);
    runtime.Run();

    return 0;
}