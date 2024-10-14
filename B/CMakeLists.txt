project(B)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LIBRARY_TYPE STATIC)
else ()
    set(LIBRARY_TYPE MODULE)
endif ()

add_library(${PROJECT_NAME} ${LIBRARY_TYPE})

target_sources(${PROJECT_NAME} PRIVATE
        src/b.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include /opt/homebrew/include)
