cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 23)

set(BUILD_PROJECT_NAME RNGOEngine_RuntimeBuild)
project(${BUILD_PROJECT_NAME})

set(EDITOR_ASSET_DIR_ABSOLUTE "${CMAKE_CURRENT_SOURCE_DIR}/EditorAssets")

option(RNGOENGINE_UNITY_BUILD "Enable Unity Build for Editor" ON)

# Include Runtime
add_subdirectory(
        ${CMAKE_CURRENT_SOURCE_DIR}/../Runtime
        ${CMAKE_CURRENT_BINARY_DIR}/Runtime
)

add_executable(${BUILD_PROJECT_NAME} main.cpp
        include/RuntimeBuild.h
        src/RuntimeBuild.cpp
)

target_include_directories(${BUILD_PROJECT_NAME} PUBLIC include)

# Libraries and C++ Version
target_link_libraries(${BUILD_PROJECT_NAME} PUBLIC RNGOEngine_Core)

# Editor Asset Directories
set(EDITOR_ASSETS_DIR "EditorAssets")
target_compile_definitions(${BUILD_PROJECT_NAME} PRIVATE
        EDITOR_ASSETS_DIR="${EDITOR_ASSETS_DIR}"
        EDITOR_MODELS_DIR="${EDITOR_ASSETS_DIR}/Models"
        EDITOR_TEXTURES_DIR="${EDITOR_ASSETS_DIR}/Textures"
        EDITOR_SHADERS_DIR="${EDITOR_ASSETS_DIR}/Shaders"
)

# Include assets in build.
file(MAKE_DIRECTORY ${EDITOR_ASSETS_DIR})
set(COPY_PROJECT_NAME RNGOEngine_Editor_Assets)
add_custom_target(${COPY_PROJECT_NAME}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${EDITOR_ASSET_DIR_ABSOLUTE} ${CMAKE_CURRENT_BINARY_DIR}/EditorAssets
)
add_dependencies(${BUILD_PROJECT_NAME} ${COPY_PROJECT_NAME})
