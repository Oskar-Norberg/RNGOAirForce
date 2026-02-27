cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 23)

set(BUILD_PROJECT_NAME RNGOEngine_RuntimeBuild)
project(${BUILD_PROJECT_NAME})

set(ASSET_DIR_ABSOLUTE "${CMAKE_CURRENT_SOURCE_DIR}/assets")

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
set(PROJECT_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(ASSET_CANDIDATE1 "${PROJECT_ROOT_DIR}/asset")
set(ASSET_CANDIDATE2 "${PROJECT_ROOT_DIR}/assets")

if(EXISTS "${ASSET_CANDIDATE1}")
    set(ASSET_SOURCE_DIR "${ASSET_CANDIDATE1}")
elseif(EXISTS "${ASSET_CANDIDATE2}")
    set(ASSET_SOURCE_DIR "${ASSET_CANDIDATE2}")
else()
    message(WARNING "No asset directory found at ${ASSET_CANDIDATE1} or ${ASSET_CANDIDATE2}. Skipping asset copy.")
endif()

if(DEFINED ASSET_SOURCE_DIR)
    add_custom_command(TARGET ${BUILD_PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${BUILD_PROJECT_NAME}>"
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${ASSET_SOURCE_DIR}"
            "$<TARGET_FILE_DIR:${BUILD_PROJECT_NAME}>"
    )
endif()