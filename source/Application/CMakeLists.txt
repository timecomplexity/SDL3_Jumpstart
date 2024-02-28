project(Application)


set(HEADERS
    Export.h
    LVApplication.h
)

set(SOURCES
    LVApplication.cpp
)

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2-static
    SDL2::SDL2main
    Vulkan::Vulkan
    Logger
    SDLSystem
    Render
)

target_compile_definitions(${PROJECT_NAME} PRIVATE LV_APPLICATION_EXPORT)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${LV_LOGGER_INC}
    ${LV_SDLSYSTEM_INC}
    ${SDL2_INCLUDE_DIRS}
    ${LV_RENDER_INC}
)
