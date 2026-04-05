param (
    [Alias("r")]
    [Switch]$Release,

    [Alias("d")]
    [Switch]$Debug,

    [Alias("t")]
    [Switch]$Test
)

# setup error handling
$ErrorActionPreference = "Stop"

# build type
$BuildType = "Debug"
$PresetName = "conan-debug"

if ($Release) {
    $BuildType = "Release"
    $PresetName = "conan-release"
}

Write-Host "--- Starting Generic Build Process ($BuildType) ---" -ForegroundColor Cyan

# conan install
Write-Host "Conan installing dependencies..." -ForegroundColor Yellow
conan install . --output-folder=. --build=missing --update -s build_type=$BuildType

# cmake configuration
Write-Host "Configuring CMake..." -ForegroundColor Yellow
$TestFlag = if ($Test) { "ON" } else { "OFF" }

if ($Test) { Write-Host "[TEST MODE ENABLED]" -ForegroundColor Magenta }

cmake --preset conan-default -DBUILD_TESTING=$TestFlag

# build
Write-Host "Building project ($BuildType)..." -ForegroundColor Yellow
cmake --build --preset $PresetName

# test
if ($Test) {
    Write-Host "`nRunning Google Tests..." -ForegroundColor Cyan
    # CTest is smart enough to find the tests via the preset
    ctest --preset $PresetName --output-on-failure
    Write-Host "All tests completed!" -ForegroundColor Green
}

Write-Host "`n[SUCCESS] Build complete!" -ForegroundColor Green

# conan package
Write-Host "Creating Conan package..." -ForegroundColor Cyan
conan create . --build=missing -s build_type=$BuildType