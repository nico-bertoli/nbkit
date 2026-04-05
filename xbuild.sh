#!/bin/bash
set -e

BUILD_TYPE="Debug"
PRESET_NAME="conan-debug"
TEST=false

while getopts "rdt" opt; do
  case $opt in
    r) BUILD_TYPE="Release"; PRESET_NAME="conan-release" ;;
    d) BUILD_TYPE="Debug";   PRESET_NAME="conan-debug" ;;
    t) TEST=true ;;
    *) echo "Usage: ./xbuild.sh [-r] [-d] [-t]"; exit 1 ;;
  esac
done

echo "--- Starting Build ($BUILD_TYPE) ---"

conan profile detect --force >/dev/null 2>&1

conan install . --output-folder=. --build=missing --update -s build_type=$BUILD_TYPE

echo "Configuring CMake..."

if [ "$TEST" = true ]; then
    cmake --preset $PRESET_NAME -DBUILD_TESTING=ON
else
    cmake --preset $PRESET_NAME
fi

echo "Building project..."


cmake --build --preset $PRESET_NAME

if [ "$TEST" = true ]; then
    echo -e "\nRunning Tests..."
    cd build/$BUILD_TYPE
    ctest --output-on-failure
    cd ../..
fi

echo -e "\n[SUCCESS] Build complete!"