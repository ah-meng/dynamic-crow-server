project(${PROJECT_NAME})

# 스레드 라이브러리 찾기
find_package(Threads REQUIRED)


# FetchContent 모듈 포함
include(FetchContent)

# ASIO 라이브러리 불러오기
FetchContent_Declare(
        asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG        asio-1-18-2   # 원하는 버전에 맞게 태그를 설정하세요.
)

# ASIO FetchContent를 부트스트랩
FetchContent_MakeAvailable(asio)


add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(${PROJECT_NAME} PRIVATE
        main.cpp
        src/CrowHttpServer.cpp
)

# 스레드 라이브러리 링크
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
target_link_libraries(${PROJECT_NAME} PRIVATE Common Util)

# ASIO 라이브러리의 include 디렉토리 추가
target_include_directories(${PROJECT_NAME} PRIVATE ${asio_SOURCE_DIR}/asio/include)

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

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32 mswsock)
endif ()