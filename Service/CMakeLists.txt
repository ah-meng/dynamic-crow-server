project(${PROJECT_NAME})

# 스레드 라이브러리 찾기
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        /opt/homebrew/include
)

target_sources(${PROJECT_NAME} PRIVATE
        main.cpp
        src/CrowHttpServer.cpp
)

# 스레드 라이브러리 링크
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
target_link_libraries(${PROJECT_NAME} PRIVATE Common Util)

# 디버그로 빌드하는 경우, 사용하는 프로젝트를 정적으로 추가하여 빌드
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (ENABLE_A_ENDPOINT)
        target_link_libraries(${PROJECT_NAME} PRIVATE A)
        add_compile_definitions(${PROJECT_NAME} PRIVATE ENABLE_A_ENDPOINT)
    endif ()

    if (ENABLE_B_ENDPOINT)
        target_link_libraries(${PROJECT_NAME} PRIVATE B)
        add_compile_definitions(${PROJECT_NAME} PRIVATE ENABLE_B_ENDPOINT)
    endif ()
endif ()