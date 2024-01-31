cmake_minimum_required(VERSION 3.14)
project(decide)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g")

file(GLOB SOURCES "src/*.cpp")
file(GLOB TESTS "test/*.cpp")

list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/googletest-src/googletest/include)


include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()
add_executable(decide ${SOURCES} src/main.cpp)
add_executable(CMVTest ${TESTS} ${SOURCES})
target_link_libraries(CMVTest GTest::gtest_main GTest::gmock_main)
include(GoogleTest)
gtest_discover_tests(CMVTest)