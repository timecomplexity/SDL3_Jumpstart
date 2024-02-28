cmake_minimum_required(VERSION 3.26.0)

# Set Project Names
set(VULKAN_PLAYGROUND_PROJECT "Playground")

project(${VULKAN_PLAYGROUND_PROJECT} VERSION 0.1)

# Variables used across all projects
set(LV_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(LV_BUILD_DIR "${LV_ROOT}/build")
set(LV_SRC_DIR "${LV_ROOT}/source")
set(LV_INC_DIR "${LV_ROOT}/include")
set(LV_VENDOR_DIR "${LV_INC_DIR}/vendor")
set(LV_SHADER_DIR "${LV_ROOT}/shaders")

# Project directories
set(LV_CORE_DIR "${LV_SRC_DIR}/Core")
set(LV_LOGGER_DIR "${LV_CORE_DIR}/Logger")
set(LV_TIME_DIR "${LV_CORE_DIR}/Time")
set(LV_UTILS_DIR "${LV_CORE_DIR}/Utilities")
set(LV_RENDER_DIR "${LV_SRC_DIR}/Render")
set(LV_SDLSYSTEM_DIR "${LV_SRC_DIR}/SDLSystem")
set(LV_APPLICATION_DIR "${LV_SRC_DIR}/Application")

# Important Include directories
set(LV_LOGGER_INC "${LV_CORE_DIR}/Logger")
set(LV_TIME_INC "${LV_CORE_DIR}/Time")
set(LV_UTILS_INC "${LV_CORE_DIR}/Utilities")
set(LV_RENDER_INC "${LV_RENDER_DIR}")
set(LV_APPLICATION_INC "${LV_APPLICATION_DIR}")

# Set CMake output locations to keep things clean
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${LV_BUILD_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${LV_BUILD_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${LV_BUILD_DIR}/bin")

set(CMAKE_CXX_STANDARD 17)

# We do this so we don't get a warning about not using these variables
set(IGNORE_VARS "${COMPILE_SHADERS}${CMAKE_BUILD_TYPE}")

if(MSVC)
    # Enable configuring VS Solution folder structure.
    # https://stackoverflow.com/questions/57163098/folder-structure-for-a-visual-studio-2017-with-cmake
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif(MSVC)

#find_package(SDL2 CONFIG REQUIRED)

# AUTO_LOCATE_VULKAN - accepted value ON or OFF
# ON  - Use CMake to auto locate the Vulkan SDK.
# OFF - Vulkan SDK path can be specified manually. This is helpful to test the build on various Vulkan version.
# https://github.com/PacktPublishing/Learning-Vulkan/blob/master/Chapter%2003/HandShake/CMakeLists.txt
message(STATUS "Attempting auto locate Vulkan using CMake......")

# Find Vulkan Path using CMake's Vulkan Module
# This will return Boolean 'Vulkan_FOUND' indicating the status of find as success(ON) or fail(OFF).
# Include directory path - 'Vulkan_INCLUDE_DIRS' and 'Vulkan_LIBRARY' with required libraries.
find_package(Vulkan QUIET)
        
if(NOT Vulkan_FOUND)
    # CMake may fail to locate the libraries but could be able to 
    # provide some path in Vulkan SDK include directory variable
    # 'Vulkan_INCLUDE_DIRS', try to extract path from this.
    message(STATUS "Failed to locate Vulkan SDK, retrying again...")
    if(EXISTS "${VULKAN_PATH}")
        message(STATUS "Successfully located the Vulkan SDK: ${VULKAN_PATH}")
    else()
        message("Error: Unable to locate Vulkan SDK. Trying to locate with environment variables.")

        set(VULKAN_PATH "$ENV{VK_SDK_PATH}")
        message("Using environment variable specified path: ${VK_SDK_PATH}")

        set(Vulkan_INCLUDE_DIRS "${VK_SDK_PATH}/Include")
        set(Vulkan_LIBRARIES "${VK_SDK_PATH}/Lib")

        find_package(Vulkan)
    endif()
endif()


# Check if manual set path exists
if(NOT Vulkan_FOUND)
    message("Error: Unable to locate this Vulkan SDK path VK_SDK_PATH: $ENV{VK_SDK_PATH}, please specify correct path.")
    return()
endif()

find_package(SDL2 REQUIRED)

#set(LV_BUILD_TESTS ON CACHE BOOL "Whether tests should be built")
#if(LV_BUILD_TESTS)
#    find_package(GTest CONFIG REQUIRED)
#endif()

# Automatically define a custom macro if we're in debug.
# https://stackoverflow.com/questions/72328810/how-to-check-for-current-cmake-build-type-in-c
add_compile_definitions("LV_DEBUG=$<CONFIG:Debug>")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${VULKAN_PLAYGROUND_PROJECT})

include_directories(
    include
    ${LV_VENDOR_DIR}
    ${LV_SDLSYSTEM_DIR}
    ${LV_RENDER_DIR}
)

add_subdirectory(source)
add_subdirectory(shaders)

set(HEADERS "")

set(SOURCES
    ${LV_SRC_DIR}/main.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${LV_LOGGER_INC}
    ${LV_APPLICATION_INC}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Logger
    Application
)

#if (WIN32)
# copy the .dll file to the same folder as the executable
#add_custom_command(
#    TARGET ${PROJECT_NAME} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#    $<TARGET_FILE:SDL2::SDL2>
#    $<TARGET_FILE_DIR:${PROJECT_NAME}>
#    VERBATIM)
#endif()
