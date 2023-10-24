project(obj_reader)
cmake_minimum_required(VERSION 3.16)

# add the obj_reader as a single target:
add_library(obj_reader INTERFACE)

target_include_directories(obj_reader
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include(GNUInstallDirs)

install(DIRECTORY include/obj_reader DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# define the export of our cmake target:
install(
    TARGETS obj_reader
    EXPORT obj_readerTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT obj_readerTargets
    FILE obj_readerTargets.cmake
    NAMESPACE obj_reader::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/obj_reader
)

# include some helper macros for generating cmake config files:
include(CMakePackageConfigHelpers)

# create the cmake config files:
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/obj_readerConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/obj_reader
)

# install the configuration files that we using the helper macros above:
install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/obj_readerConfig.cmake" # cmake config file
    "${CMAKE_CURRENT_BINARY_DIR}/obj_readerConfigVersion.cmake" # cmake version file
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/obj_reader
)

set(version 1.0.0)

# generate the version file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/obj_readerConfigVersion.cmake"
    VERSION "${version}"
    COMPATIBILITY AnyNewerVersion # probably don't want to set this. Would need to check other options.
)