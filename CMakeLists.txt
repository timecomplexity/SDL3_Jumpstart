cmake_minimum_required(VERSION 3.26.0)

# Set Project Names
set(SDL_PLAYGROUND_PROJECT "Playground")

project(${SDL_PLAYGROUND_PROJECT} VERSION 0.1)

# Variables used across all projects
set(SDLPG_ROOT          "${CMAKE_CURRENT_SOURCE_DIR}")
set(SDLPG_BUILD_DIR     "${SDLPG_ROOT}/build")
set(SDLPG_SRC_DIR       "${SDLPG_ROOT}/source")
set(SDLPG_INC_DIR       "${SDLPG_ROOT}/include")
set(SDLPG_VENDOR_DIR    "${SDLPG_INC_DIR}/vendor")
set(SDLPG_SHADER_DIR    "${SDLPG_ROOT}/shaders")

# Project directories
set(SDLPG_CORE_DIR          "${SDLPG_SRC_DIR}/Core")
set(SDLPG_LOGGER_DIR        "${SDLPG_CORE_DIR}/Logger")
set(SDLPG_TIME_DIR          "${SDLPG_CORE_DIR}/Time")
set(SDLPG_UTILS_DIR         "${SDLPG_CORE_DIR}/Utilities")
set(SDLPG_RENDER_DIR        "${SDLPG_SRC_DIR}/Render")
set(SDLPG_SDLSYSTEM_DIR     "${SDLPG_SRC_DIR}/SDLSystem")
set(SDLPG_APPLICATION_DIR   "${SDLPG_SRC_DIR}/Application")

# Important Include directories
set(SDLPG_LOGGER_INC        "${SDLPG_CORE_DIR}/Logger")
set(SDLPG_TIME_INC          "${SDLPG_CORE_DIR}/Time")
set(SDLPG_UTILS_INC         "${SDLPG_CORE_DIR}/Utilities")
set(SDLPG_RENDER_INC        "${SDLPG_RENDER_DIR}")
set(SDLPG_APPLICATION_INC   "${SDLPG_APPLICATION_DIR}")

# Vendor directories and includes
set(GLEW_DIR    "${SDLPG_VENDOR_DIR}/glew")
set(GLEW_INC    "${GLEW_DIR}/include")
set(GLM_DIR     "${SDLPG_VENDOR_DIR}/glm")
set(GLM_INC     "${GLM_DIR}")
set(SPDLOG_DIR  "${SDLPG_VENDOR_DIR}/glm")
set(SPDLOG_INC  "${SPDLOG_DIR}")

# Set CMake output locations to keep things clean
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${SDLPG_BUILD_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${SDLPG_BUILD_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${SDLPG_BUILD_DIR}/bin")

set(CMAKE_CXX_STANDARD 17)

# We do this so we don't get a warning about not using these variables
set(IGNORE_VARS "${COMPILE_SHADERS}${CMAKE_BUILD_TYPE}")

if(MSVC)
    # Enable configuring VS Solution folder structure.
    # https://stackoverflow.com/questions/57163098/folder-structure-for-a-visual-studio-2017-with-cmake
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif(MSVC)

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

find_package(SDL3 REQUIRED)

# Prefer GLVND to get rid of warnings
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
set(GLEW_USE_STATIC_LIBS True)
set(GLEW_VERBOSE True)
find_package(GLEW REQUIRED)

#set(SDLPG_BUILD_TESTS ON CACHE BOOL "Whether tests should be built")
#if(SDLPG_BUILD_TESTS)
#    find_package(GTest CONFIG REQUIRED)
#endif()

# Automatically define a custom macro if we're in debug.
# https://stackoverflow.com/questions/72328810/how-to-check-for-current-cmake-build-type-in-c
add_compile_definitions("SDLPG_DEBUG=$<CONFIG:Debug>")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${SDL_PLAYGROUND_PROJECT})

include_directories(
    include
    ${SDLPG_VENDOR_DIR}
    ${SDLPG_SDLSYSTEM_DIR}
    ${SDLPG_RENDER_DIR}
)

add_subdirectory(source)
add_subdirectory(shaders)

set(HEADERS "")

set(SOURCES
    ${SDLPG_SRC_DIR}/main.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${SDLPG_LOGGER_INC}
    ${SDLPG_APPLICATION_INC}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Logger
    Application
)

if (WIN32)
# copy the .dll file to the same folder as the executable
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3::SDL3>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
    VERBATIM)
endif()
