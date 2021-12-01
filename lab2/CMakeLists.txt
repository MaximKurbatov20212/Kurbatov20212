cmake_minimum_required(VERSION 3.10)

# set the project name
project(test_interpreter VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
  main
  main.cpp
  command.cpp
  interpreter.cpp
  my_stack.cpp
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
  test_interpreter
  interpreter_test.cpp
  command.cpp
  interpreter.cpp
  my_stack.cpp
)

if ( CMAKE_COMPILER_IS_GNUCC )
  target_compile_options(test_interpreter PRIVATE "-Wall")
endif()
if ( MSVC )
  target_compile_options(test_interpreter PRIVATE "/W4")
endif()

target_link_libraries(
  test_interpreter
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_interpreter)
#gtest_discover_tests(test_interpreter DISCOVERY_TIMEOUT 30)