#!/bin/bash

conan install . --output-folder=build --build=missing
cd build

 #------------------ google tests
if [[ "$1" == "--test" ]]; then
    
    cmake -S .. -B . -DBUILD_TESTING=ON -DCMAKE_TOOLCHAIN_FILE=build/build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
    make

    ctest --output-on-failure   # Run tests with output on failure

    echo ""
    echo "All tests completed!"
    
#------------------ normal build
else 
    cmake -S .. -B . -DCMAKE_TOOLCHAIN_FILE=build/build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
    make
fi
