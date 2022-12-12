cmake_minimum_required (VERSION 3.18)
project (network VERSION 0.0.1 LANGUAGES CXX)

# Determine if stun is built as a subproject (using add_subdirectory) or if it is the master project.

if (NOT DEFINED NETEWORK_MASTER_PROJECT)
  set (NETWORK_MASTER_PROJECT OFF)

  if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set (NETWORK_MASTER_PROJECT ON)
  endif ()
endif ()


# Set an additional path to the CMake modules and connect them

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(NestingFileSearch)
include(CMakeDependentOption)


# Options available for project customization

cmake_dependent_option (NETWORK_BUILD_SHARED_LIBS "Build the project as a dynamic library" "${BUILD_SHARED_LIBS}" "NETWORK_MASTER_PROJECT" ${NETWORK_MASTER_PROJECT})
cmake_dependent_option (NETWORK_BUILD_TESTING "Build tests for the project" "${BUILD_TESTING}" "NETWORK_MASTER_PROJECT" ${NETWORK_MASTER_PROJECT})

option (NETWORK_BUILD_APPS "Build applications" ON)
option (NETWORK_BUILD_EXAMPLE "Build examples for a project" OFF)
option (NETWORK_INSTALL "Generate a target for project installation" ON)
option (NETWORK_GENERATE_DOCUMENTATION "Generate documentation when building a project" OFF)
option (NETWORK_PEDANTIC "Enable the display of additional warnings" OFF)
option (NETWORK_WERROR "Handle all compiler warnings with errors" OFF)
option (NETWORK_MSVC_STATIC_RUNTIME "Link static runtime libraries" OFF)
option (NETWORK_ENABLE_COVERAGE "Run coverage" OFF)
option (NETWORK_ENABLE_SANITIZERS "Run static analysis" OFF)

message (STATUS "NETWORK_BUILD_SHARED_LIBS - ${NETWORK_BUILD_SHARED_LIBS}")
message (STATUS "NETWORK_BUILD_TESTING - ${NETWORK_BUILD_TESTING}")
message (STATUS "NETWORK_BUILD_APPS - ${NETWORK_BUILD_APPS}")
message (STATUS "NETWORK_BUILD_EXAMPLE - ${NETWORK_BUILD_EXAMPLE}")
message (STATUS "NETWORK_INSTALL - ${NETWORK_INSTALL}")
message (STATUS "NETWORK_GENERATE_DOCUMENTATION - ${NETWORK_GENERATE_DOCUMENTATION}")
message (STATUS "NETWORK_PEDANTIC - ${NETWORK_PEDANTIC}")
message (STATUS "NETWORK_WERROR - ${NETWORK_WERROR}")
message (STATUS "NETWORK_ENABLE_COVERAGE - ${NETWORK_ENABLE_COVERAGE}")
message (STATUS "NETWORK_ENABLE_SANITIZERS - ${NETWORK_ENABLE_SANITIZERS}")


# Configuring project output directories

if (NETWORK_MASTER_PROJECT)
  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) 
endif ( )    


# Configuring project build options

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set_property (GLOBAL PROPERTY USE_FOLDERS ON)
set_property (GLOBAL PROPERTY LINKER_LANGUAGE CXX)
string (APPEND CMAKE_DEBUG_POSTFIX "_dbg")


# Additional options for building on Windows  
if (WIN32)
    set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

    if (MSVC AND ${NETWORK_MSVC_STATIC_RUNTIME})
        set (FLAG_VARS 
            CMAKE_CXX_FLAGS 
            CMAKE_CXX_FLAGS_DEBUG 
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL 
            CMAKE_CXX_FLAGS_RELWITHDEBINFO
        )

        foreach (FLAG_VAR ${FLAG_VARS})
            if (${FLAG_VAR} MATCHES "/MD")
                string (REGEX REPLACE "/MD" "/MT" ${FLAG_VAR} "${${FLAG_VAR}}")
            endif ()
        endforeach ()
        
        string (APPEND CMAKE_DEBUG_POSTFIX "_mt")
        string (APPEND CMAKE_RELEASE_POSTFIX "_mt")
    else ()
        string (APPEND CMAKE_DEBUG_POSTFIX "_md")
        string (APPEND CMAKE_RELEASE_POSTFIX "_md")
    endif ()
endif ()


# Enable coverage

if (NETWORK_ENABLE_COVERAGE AND UNIX)
    list (APPEND CMAKE_CXX_FLAGS "--coverage -g -O0")
    find_package(Threads REQUIRED)
endif ()


# Enable sanitizers

if(NETWORK_ENABLE_SANITIZERS)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=leak -fsanitize=undefined")
endif()


# Adding subdirectories to the project

add_subdirectory (lib)

if (NETWORK_BUILD_APPS)
    add_subdirectory (app)
endif ()

if (NETWORK_BUILD_TESTING)
    include (CTest)
    enable_testing ()
    add_subdirectory (test)
endif ()

if (NETWORK_BUILD_EXAMPLE)
    add_subdirectory (example)
endif ()
