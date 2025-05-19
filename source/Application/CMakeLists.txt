project(Application)


set(HEADERS
    Export.h
    SDLPGApplication.h
)

set(SOURCES
    SDLPGApplication.cpp
)

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})


target_link_libraries(${PROJECT_NAME}
    SDL3::SDL3
    Logger
    SDLSystem
    Render
)

if("${GRAPHICS_API}" STREQUAL "VULKAN")
    target_link_libraries(${PROJECT_NAME}
        Vulkan::Vulkan
    )
endif()

if("${GRAPHICS_API}" STREQUAL "OPENGL")
    target_link_libraries(${PROJECT_NAME}
        libglew_static
    )
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE SDLPG_APPLICATION_EXPORT)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${SDLPG_LOGGER_INC}
    ${SDLPG_SDLSYSTEM_INC}
    ${SDL3_INCLUDE_DIRS}
    ${SDLPG_RENDER_INC}
)

if("${GRAPHICS_API}" STREQUAL "OPENGL")
    target_include_directories(${PROJECT_NAME} PUBLIC
    ${GLEW_INC}
)
endif()
