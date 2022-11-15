# Create and configure a library target

# Find the dependencies

find_package(Boost REQUIRED)

# Define the library type
if (NETWORK_BUILD_SHARED_LIBS)
    set (NETWORK_LIBRARY_TYPE SHARED)
else ()
    set (NETWORK_LIBRARY_TYPE STATIC)
endif ()

add_library (network ${NETWORK_LIBRARY_TYPE})
add_library (wh::network ALIAS network)
message (STATUS "NETWORK_LIBRARY_TYPE - ${NETWORK_LIBRARY_TYPE}")

# Describing the list of source files

NestingFileSearch (NETWORK_HEADERS
    RECURSIVE
    EXTENSIONS ".h"
    DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

NestingFileSearch (NETWORK_SOURCES
    RECURSIVE
    EXTENSIONS ".cc"
    DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_sources(network
    PUBLIC 
        ${NETWORK_HEADERS}
    PRIVATE
        ${NETWORK_SOURCES}
)

target_include_directories(network
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(network
    PRIVATE
        Boost::boost
)

foreach(HEADER ${NETWORK_HEADERS})
    set_target_properties(network
        PROPERTIES
            PUBLIC_HEADER ${HEADER}
    )
endforeach()

# Create an installation target

if(NETWORK_INSTALL)
    install(
        TARGETS network
        EXPORT network-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/network
    )
endif()