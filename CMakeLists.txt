cmake_minimum_required(VERSION 3.5)
project(founder VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})

link_directories(${CMAKE_BINARY_DIR}/lib ${CMAKE_BINARY_DIR}/bin)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
message(STATUS "SRC_DIR=${SRC_DIR}")
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
message(STATUS "LIBRARY_OUTPUT_DIRECTORY=${LIBRARY_OUTPUT_DIRECTORY}")

# Override reyengine options
set(REY_ENABLE_LUA ON CACHE BOOL "" FORCE)
add_subdirectory(reyengine)
add_executable(${PROJECT_NAME}
        src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        src
)

target_link_libraries(${PROJECT_NAME} ReyEngine2D)


########################################################################
function(install_resource_folder TARGET FOLDER)
    # Optional third parameter: destination directory (defaults to FOLDER if not provided)
    if(${ARGC} GREATER 2)
        set(DEST_FOLDER ${ARGV2})
    else()
        set(DEST_FOLDER ${FOLDER})
    endif()

    message("==================")
    message("Setting up resource copying for folder " ${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER})
    message("  Destination: " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${DEST_FOLDER})

    # Create a custom target that always runs and copies resources
    # Replace slashes with underscores to make a valid target name
    string(REPLACE "/" "_" FOLDER_SAFE "${FOLDER}")
    set(COPY_TARGET "copy_${FOLDER_SAFE}_${TARGET}")
    add_custom_target(${COPY_TARGET} ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/${FOLDER}
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${DEST_FOLDER}
            COMMENT "Copying resources from ${FOLDER}/ to ${DEST_FOLDER}/"
            VERBATIM
    )

    # Make the main target depend on resource copying
    add_dependencies(${TARGET} ${COPY_TARGET})

    message("  Resources will be copied on every build")
    message("==================")
endfunction()
########################################################################
# install resource folders here - must be called after add_executable
install_resource_folder(${PROJECT_NAME} resources)
install_resource_folder(${PROJECT_NAME} reyengine/reyengine/resources reyengine/resources)
#install_resource_folder(${PROJECT_NAME} yaml)