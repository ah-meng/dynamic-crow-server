project(A)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LIBRARY_TYPE STATIC)
else ()
    set(LIBRARY_TYPE MODULE)
endif ()

add_library(${PROJECT_NAME} ${LIBRARY_TYPE})

target_sources(${PROJECT_NAME} PRIVATE
        src/a.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC Common)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)