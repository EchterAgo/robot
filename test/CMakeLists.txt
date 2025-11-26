cmake_minimum_required(VERSION 3.14)

project(robotTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(robot REQUIRED)
  enable_testing()
endif()

# ---- Tests ----

add_executable(
	robot_test
    source/Clipboard.cc
    source/Keyboard.cc
    source/Main.cc
    source/Memory.cc
    source/Mouse.cc
    source/Process.cc
    source/Screen.cc
    source/Targa.cc
    source/Timer.cc
    source/Types.cc
    source/Window.cc
	)
target_link_libraries(robot_test PRIVATE robot::robot)
target_compile_features(robot_test PRIVATE cxx_std_17)

add_test(NAME robot_test COMMAND robot_test)

# ---- End-of-file commands ----

add_folders(Test)
