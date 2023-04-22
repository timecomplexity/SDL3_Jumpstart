project(Utilities)

set(HEADERS
  Assert.h
)

set(SOURCES
)

if(OSDL_ENABLE_ASSERTS)
  add_definitions(DLV_ENABLE_ASSERTS)
endif()

add_subdirectory(test)
