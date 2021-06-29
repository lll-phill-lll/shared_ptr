# from https://google.github.io/googletest/quickstart-cmake.html
cmake_minimum_required(VERSION 3.14)
project(my_shared_ptr)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  unit_tests
  basic_methods_ut.cpp
  general_ut.cpp
)
target_link_libraries(
  unit_tests
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)

