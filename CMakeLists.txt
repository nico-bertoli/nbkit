cmake_minimum_required(VERSION 3.22)
project(nbkit VERSION 1.0.0)

#----------------------- base configuration
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

#----------------------- find source files
file(
    GLOB_RECURSE SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/nbkit/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/nbkit/*.h"
)

if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in the nbkit directory!")
endif()

#----------------------- create library
add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(
    ${PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

#----------------------- installation logic
install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
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
    
    if(TEST_FILES)
        add_executable(${PROJECT_NAME}_tests ${TEST_FILES})  
        target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME} GTest::gtest_main) 
        
        include(GoogleTest)  
        gtest_discover_tests(${PROJECT_NAME}_tests)
    else()
        message(WARNING "No test files found in ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp. Skipping test target creation.")
    endif()
endif()