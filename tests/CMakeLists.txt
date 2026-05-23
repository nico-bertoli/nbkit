file(GLOB TEST_FILES CONFIGURE_DEPENDS "*.cpp")
list(REMOVE_ITEM TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test_log_override.cpp")

add_executable(${CMAKE_PROJECT_NAME}_tests ${TEST_FILES})
add_executable(${CMAKE_PROJECT_NAME}_log_override_tests test_log_override.cpp)

foreach(target ${CMAKE_PROJECT_NAME}_tests ${CMAKE_PROJECT_NAME}_log_override_tests)
    target_link_libraries(${target} PRIVATE ${CMAKE_PROJECT_NAME} GTest::gtest_main)
    gtest_discover_tests(${target})
endforeach()
