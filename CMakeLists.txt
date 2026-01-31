#----------------------- base configuration
cmake_minimum_required(VERSION 3.22)
project(nbkit VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

#----------------------- create library
file(GLOB_RECURSE SRC "${CMAKE_CURRENT_SOURCE_DIR}/nbkit/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/nbkit/*.h") 
add_library(${PROJECT_NAME} ${SRC}) 
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

#----------------------- create conan package
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY nbkit/
    DESTINATION include/nbkit
    FILES_MATCHING PATTERN "*.h"
)

#----------------------- Google tests
option(BUILD_TESTING "Build the testing tree" OFF)

if(BUILD_TESTING)
    enable_testing() 
    find_package(GTest REQUIRED)
    file(GLOB_RECURSE TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp") 
    add_executable(${PROJECT_NAME}_tests ${TEST_FILES})  
    target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main) 
    target_include_directories(${PROJECT_NAME}_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

    # include google test cmake functions
    include(GoogleTest)  
    # discover and register all tests with CTest
    gtest_discover_tests(${PROJECT_NAME}_tests)
endif()