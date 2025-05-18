project(SDLSystem)


set(HEADERS
    Export.h
    SDLScopedMutex.h
    SDLState.h
    SDLWindow.h
)

set(SOURCES
    SDLState.cpp
    SDLWindow.cpp
)

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} SDL3::SDL3 Logger)
target_compile_definitions(${PROJECT_NAME} PRIVATE SDLPG_SDLSYSTEM_EXPORT)

target_include_directories(${PROJECT_NAME} PUBLIC ${SDLPG_LOGGER_INC})
