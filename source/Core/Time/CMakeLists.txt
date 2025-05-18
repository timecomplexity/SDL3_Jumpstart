project(Time)

set(HEADERS
  Clock.h
  Export.h
)

set(SOURCES
  Clock.cpp
)

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3)
target_compile_definitions(${PROJECT_NAME} PRIVATE SDLPG_CORETIME_EXPORT)
