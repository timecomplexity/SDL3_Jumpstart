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
target_link_libraries(${PROJECT_NAME} SDL2::SDL2 Logger)
target_compile_definitions(${PROJECT_NAME} PRIVATE LV_SDLSYSTEM_EXPORT)

target_include_directories(${PROJECT_NAME} PUBLIC ${LV_LOGGER_INC})
