if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/robot-${PROJECT_VERSION}"
      CACHE STRING ""
  )
  set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package robot)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT robot_Development
)

install(
    TARGETS robot_robot
    EXPORT robotTargets
    RUNTIME #
    COMPONENT robot_Runtime
    LIBRARY #
    COMPONENT robot_Runtime
    NAMELINK_COMPONENT robot_Development
    ARCHIVE #
    COMPONENT robot_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    robot_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE robot_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(robot_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${robot_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT robot_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${robot_INSTALL_CMAKEDIR}"
    COMPONENT robot_Development
)

install(
    EXPORT robotTargets
    NAMESPACE robot::
    DESTINATION "${robot_INSTALL_CMAKEDIR}"
    COMPONENT robot_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
