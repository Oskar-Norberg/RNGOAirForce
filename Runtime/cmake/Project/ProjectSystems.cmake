set(PROJECT_SPECIFIC_SYSTEMS RNGOGame_Systems)
add_library(${PROJECT_SPECIFIC_SYSTEMS} INTERFACE
        include/ECS/Systems/Project/SplineAttachmentSystem.h
        include/ECS/Systems/Project/SplineMovementSystem.h
        include/ECS/Systems/Project/ProjectileSpawningSystem.h
        include/ECS/Systems/Project/DestroyAfterTimeSystem.h
        include/ECS/Systems/Project/BulletMovementSystem.h
        include/ECS/Systems/Project/BulletDestructionSystem.h
        include/ECS/Systems/Project/RailsShooterCameraSystem.h
        include/ECS/Systems/Project/SetCameraPosToPlayerSystem.h
        include/ECS/Systems/Project/TriggerSceneLoadOnShotByPlayerSystem.h
        include/ECS/Systems/Project/TriggerSceneLoadOnPlayerCollisionSystem.h
)
target_include_directories(${PROJECT_SPECIFIC_SYSTEMS} INTERFACE include)
target_link_libraries(${PROJECT_SPECIFIC_SYSTEMS} INTERFACE EnTT ${SCENE_PROJECT_NAME})
target_link_libraries(${PROJECT_SPECIFIC_SYSTEMS} INTERFACE
        ${SCENE_PROJECT_NAME}
        ${SYSTEM_PROJECT_NAME}
        ${PROFILING_PROJECT_NAME}
        ${UTILITIES_PROJECT_NAME}
        ${LOGGING_PROJECT_NAME}
)
