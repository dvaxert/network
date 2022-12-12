# Create and configure a library target

# Find the dependencies

find_package(Boost REQUIRED)
find_package(Utils REQUIRED)

# Define the library type
if (NETWORK_BUILD_SHARED_LIBS)
    set (NETWORK_LIBRARY_TYPE SHARED)
else ()
    set (NETWORK_LIBRARY_TYPE STATIC)
endif ()

add_library (network ${NETWORK_LIBRARY_TYPE})
add_library (Wormhole::network ALIAS network)
message (STATUS "NETWORK_LIBRARY_TYPE - ${NETWORK_LIBRARY_TYPE}")

# Describing the list of source files

NestingFileSearch (UTILS_HEADERS
    RECURSIVE
    EXTENSIONS ".h"
    DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
    EXCLUDE "*.in"
)

NestingFileSearch (NETWORK_SOURCES
    RECURSIVE
    EXTENSIONS ".cc"
    DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_sources (${PROJECT_NAME}
    PRIVATE
        ${UTILS_SOURCES}
        ${UTILS_HEADERS}
)

target_include_directories(network
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(network
    PRIVATE
        Boost::boost
        Wormhole::network
)

# Create an installation target

if (UTILS_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    include (GNUInstallDirs)
    include (CMakePackageConfigHelpers)

    set (UTILS_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
    set (UTILS_PKGCONFIG_DIR ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
    set (VERSION_CONFIG ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake)
    set (PROJECT_CONFIG ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake)
    set (UTILS_TARGETS_EXPORT_NAME ${PROJECT_NAME}-targets)

    # Generate the version, config and target files into the build directory.
    write_basic_package_version_file (
        ${VERSION_CONFIG}
        VERSION ${UTILS_VERSION}
        COMPATIBILITY AnyNewerVersion
    )
    
    configure_file (
        "${PROJECT_SOURCE_DIR}/cmake/network.pc.in"
        "${UTILS_PKGCONFIG_DIR}"
        @ONLY
    )

    configure_package_config_file (
        ${PROJECT_SOURCE_DIR}/cmake/network-config.cmake.in
        ${PROJECT_CONFIG}
        INSTALL_DESTINATION ${UTILS_CMAKE_DIR}
    )

    # Install the library
    install (
        TARGETS ${PROJECT_NAME} 
        EXPORT ${UTILS_TARGETS_EXPORT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        FRAMEWORK DESTINATION "."
        INCLUDES
    )

    # Install headers.
    install (
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    # Use a namespace because CMake provides better diagnostics for namespaced imported targets.
    export (
        TARGETS ${PROJECT_NAME}
        NAMESPACE Wormhole::
        FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-targets.cmake
    )

    # Install version, config and target files.
    install (
        FILES ${PROJECT_CONFIG} ${VERSION_CONFIG}
        DESTINATION ${UTILS_CMAKE_DIR}
    )

    install (
        EXPORT ${PROJECT_NAME}-targets 
        DESTINATION ${UTILS_CMAKE_DIR}
        NAMESPACE Wormhole::
    )
    
    # $<TARGET_PDB_FILE:tgt> generates an error if the library is built with the /MT flag
    # so the path to the pdb file is created from the available variables
    install (
        FILES $<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_BASE_NAME:${PROJECT_NAME}>.pdb
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        OPTIONAL
    )
endif ()