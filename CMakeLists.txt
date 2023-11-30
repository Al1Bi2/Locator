cmake_minimum_required(VERSION 3.14)
include(FetchContent)

project(locator)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(locator)

add_subdirectory(locator)
add_subdirectory(tests)

FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
enable_testing()

FetchContent_Declare(
json

GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git
GIT_TAG v3.10.0)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
spdlog

GIT_REPOSITORY https://github.com/gabime/spdlog.git
GIT_TAG v1.12.0)
FetchContent_MakeAvailable(spdlog)