set(MATH_PROJECT_NAME RNGOEngine_Math)
add_library(${MATH_PROJECT_NAME} STATIC
        include/Math/2D/Point2D.h
        include/Math/2D/AABB2D.h

        include/Math/3D/Point3D.h
        include/Math/3D/AABB3D.h

        include/Math/3D/CollisionChecks.h
        src/Math/3D/CollisionChecks.cpp
)
target_include_directories(${MATH_PROJECT_NAME} PUBLIC include)
target_link_libraries(${MATH_PROJECT_NAME} PUBLIC glm)
target_link_libraries(${MATH_PROJECT_NAME} PUBLIC
        ${PROFILING_PROJECT_NAME}
        ${UTILITIES_PROJECT_NAME}
        ${LOGGING_PROJECT_NAME}
        ${CONCEPTS_PROJECT_NAME}
)
