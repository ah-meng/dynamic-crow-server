# Service/Lib/crow.cmake

# FetchContent 모듈 포함
include(FetchContent)

# ASIO 라이브러리 불러오기
FetchContent_Declare(
        asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG asio-1-18-2   # 원하는 버전에 맞게 태그를 설정하세요.
)

# Crow 라이브러리 불러오기
FetchContent_Declare(
        crow
        GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
        GIT_TAG v1.2  # 원하는 버전에 맞게 태그를 설정하세요.
)
set(ASIO_INCLUDE_DIR ${asio_SOURCE_DIR}/asio/include)
# 라이브러리 FetchContent를 부트스트랩
FetchContent_MakeAvailable(asio crow)

# Crow와 ASIO의 include 디렉토리 추가
target_include_directories(${PROJECT_NAME} PRIVATE ${asio_SOURCE_DIR}/asio/include ${crow_SOURCE_DIR}/include)
