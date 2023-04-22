if(OSDL_BUILD_TESTS)
  project(TestUtilities)

  enable_testing()

  set(SOURCES
    Assert.test.cpp
  )

  add_executable(${PROJECT_NAME} ${SOURCES})
  target_link_libraries(${PROJECT_NAME} GTest::gtest_main Logger)
  include(GoogleTest)
  gtest_discover_tests(${PROJECT_NAME})
endif()
