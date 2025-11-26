cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    robot
    VERSION 2.0.0
    DESCRIPTION "Native cross-platform system automation "
    HOMEPAGE_URL "http://getrobot.net/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    robot_robot
    source/Window.cc
    source/Bounds.cc
    source/Clipboard.cc
    source/Color.cc
    source/Hash.cc
    source/Image.cc
    source/Keyboard.cc
    source/Memory.cc
    source/Module.cc
    source/Mouse.cc
    source/Point.cc
    source/Process.cc
    source/Range.cc
    source/Screen.cc
    source/Size.cc
    source/Timer.cc
)
add_library(robot::robot ALIAS robot_robot)

# ---- Global.h generation ----

# Generate version hex from PROJECT_VERSION (e.g., 2.0.0 -> 0x020000)
string(REPLACE "." ";" VERSION_LIST ${PROJECT_VERSION})
list(GET VERSION_LIST 0 VERSION_MAJOR)
list(GET VERSION_LIST 1 VERSION_MINOR)
list(GET VERSION_LIST 2 VERSION_PATCH)
math(EXPR ROBOT_VERSION_HEX "0x${VERSION_MAJOR}0000 + 0x${VERSION_MINOR}00 + 0x${VERSION_PATCH}" OUTPUT_FORMAT HEXADECIMAL)

# Detect operating system
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(ROBOT_OS_DEFINE "#define ROBOT_OS_LINUX")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(ROBOT_OS_DEFINE "#define ROBOT_OS_MAC")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(ROBOT_OS_DEFINE "#define ROBOT_OS_WIN")
else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()

# Detect architecture (32-bit vs 64-bit)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ROBOT_ARCH_DEFINE "#define ROBOT_ARCH_64")
else()
    set(ROBOT_ARCH_DEFINE "#define ROBOT_ARCH_32")
endif()

# Configure Global.h with platform detection
configure_file(
    "${PROJECT_SOURCE_DIR}/include/robot/Global.h.in"
    "${PROJECT_BINARY_DIR}/export/robot/Global.h"
    @ONLY
)

include(GenerateExportHeader)
generate_export_header(
    robot_robot
    BASE_NAME robot
    EXPORT_FILE_NAME export/robot/robot_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(robot_robot PUBLIC ROBOT_STATIC_DEFINE)
endif()

set_target_properties(
    robot_robot PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME robot
    OUTPUT_NAME robot
)

target_include_directories(
    robot_robot ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    robot_robot SYSTEM
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(robot_robot PUBLIC cxx_std_17)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT robot_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of robot"
  )
endif()

include(cmake/dev-mode.cmake)
