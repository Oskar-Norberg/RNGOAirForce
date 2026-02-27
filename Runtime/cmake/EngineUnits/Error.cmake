set(ERROR_PROJECT_NAME RNGOEngine_ERROR)
add_library(${ERROR_PROJECT_NAME} INTERFACE
        include/Errors/EngineError.h
)
target_include_directories(${ERROR_PROJECT_NAME} INTERFACE include)
target_link_libraries(${ERROR_PROJECT_NAME} INTERFACE
        ${PROFILING_PROJECT_NAME}
        ${UTILITIES_PROJECT_NAME}
        ${LOGGING_PROJECT_NAME}
)
