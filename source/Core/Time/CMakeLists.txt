project(Time)

set(HEADERS
  Clock.h
  Export.h
)

set(SOURCES
  Clock.cpp
)

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2)
target_compile_definitions(${PROJECT_NAME} PRIVATE LV_CORETIME_EXPORT)
