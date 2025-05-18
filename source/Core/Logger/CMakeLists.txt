project(Logger)

set(HEADERS
  Export.h
  Logger.h
  LoggerLevel.h
  LoggerMessage.h
  LoggerSink.h
)

set(SOURCES
  Logger.cpp
  LoggerMessage.cpp
  LoggerSink.cpp
)

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE SDLPG_LOGGER_EXPORT)

#target_link_libraries(${PROJECT_NAME} spdlog::spdlog)
