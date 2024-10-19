project(Util)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
        PRIVATE
        src/DynamicLoader.cpp
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (WIN32)

else ()
    target_link_libraries(${PROJECT_NAME} PRIVATE dl)
endif ()