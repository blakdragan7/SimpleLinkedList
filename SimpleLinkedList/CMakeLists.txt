# CMakeList.txt : CMake project for SimpleLinkedList, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SimpleLinkedList")

# Add source to this project's executable.
add_executable (SimpleLinkedList  "SimpleLinkedList.hpp" "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SimpleLinkedList PROPERTY CXX_STANDARD 20)
endif()

# GTest
include(d:/vcpkg/scripts/buildsystems/vcpkg.cmake)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Unit Tests
# Add test cpp file
add_executable( runUnitTests tests.cpp test_complex.cpp)
# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests ${GTEST_BOTH_LIBRARIES})
add_test( runUnitTests runUnitTests )