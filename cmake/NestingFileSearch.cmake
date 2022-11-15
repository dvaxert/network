
# File search which allows to save nesting of files in the project when working in MSVC

macro (NestingFileSearch OUTPUT)
    set (options RECURSIVE APPEND)
    set (oneValueArgs "")
    set (multiValueArgs EXTENSIONS DIRECTORIES EXCLUDE_PATTERNS)
    cmake_parse_arguments (NFS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Returns an error if the passed values are incorrect

    if (NFS_UNPARSED_ARGUMENTS)
        message (FATAL_ERROR "Unknown keywords given to NestingFileSearch(): ${NFS_UNPARSED_ARGUMENTS}")
    endif ()

    if (NOT NFS_APPEND)
        unset (OUTPUT)
    endif ()

    if (NFS_RECURSIVE)
        set (GLOB_TYPE GLOB_RECURSE)
    else ()
        set (GLOB_TYPE GLOB)
    endif ()

    foreach (NFS_BASE_DIR ${NFS_DIRECTORIES})
        string (REGEX REPLACE "(.*/).*" "\\1" NFS_EXTERNAL_PATH "${NFS_BASE_DIR}")
        file (${GLOB_TYPE} NFS_LIST_DIRECTORIES LIST_DIRECTORIES TRUE "${NFS_BASE_DIR}/*")
        list (APPEND NFS_LIST_DIRECTORIES ${NFS_BASE_DIR})

        foreach (NFS_DIR ${NFS_LIST_DIRECTORIES})
            if (IS_DIRECTORY ${NFS_DIR})
                string (REGEX REPLACE "${NFS_EXTERNAL_PATH}(.*)" "\\1" NFS_GROUP_NAME "${NFS_DIR}")

                foreach (NFS_EXTENSION ${NFS_EXTENSIONS})
                    file (GLOB NFS_FILES_IN_DIRECTORY LIST_DIRECTORIES FALSE "${NFS_DIR}/*${NFS_EXTENSION}")
                endforeach ()

                if (MSVC)
                    source_group ("${NFS_GROUP_NAME}" FILES ${NFS_FILES_IN_DIRECTORY})
                endif ()

                list (APPEND ${OUTPUT} ${NFS_FILES_IN_DIRECTORY})
            endif ()
        endforeach ()
    endforeach ()

    foreach (PATTERN ${NFS_EXCLUDE_PATTERNS})
        foreach (VALUE ${${OUTPUT}})
            string(REGEX MATCH ${PATTERN} IS_MATCHED ${VALUE})

            if(NOT ${IS_MATCHED} STREQUAL "")
                list(REMOVE_ITEM ${OUTPUT} ${VALUE})
            endif()
        endforeach ()
    endforeach ()

endmacro ()