project(Render)


set(HEADERS
    Export.h
    RenderPipeline.h
)

set(SOURCES
    RenderPipeline.cpp
)

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} Logger)
target_compile_definitions(${PROJECT_NAME} PRIVATE SDLPG_RENDER_EXPORT)

target_include_directories(${PROJECT_NAME} PUBLIC ${SDLPG_LOGGER_INC})
