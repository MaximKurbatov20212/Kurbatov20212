cmake_minimum_required(VERSION 3.10)

# set the project name
project(test_any VERSION 0.1)

#SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -static-libsan -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -static-libsan -g")


if ( CMAKE_COMPILER_IS_GNUCC )
  target_compile_options(test_any PRIVATE "-Wall -Wextra")
endif()
if ( MSVC )
  target_compile_options(test_any PRIVATE "/M4")
endif()

add_executable(
  main
  main.cpp
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  test_any
  any_tests.cpp
)

target_link_libraries(
  test_any
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_any)
