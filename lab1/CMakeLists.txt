cmake_minimum_required(VERSION 3.10)

# set the project name
project(lab1 VERSION 0.1)

# add the executable
add_executable(lab1 hash_table.cpp main1.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# tests

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
  lab1
  hash_table_test.cpp
  hash_table.cpp
)
target_link_libraries(
  IntArrayTest
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(lab1)
