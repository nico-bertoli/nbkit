# nbkit

My base kit, a set of common classes that can be shared across projects.

## Installation

update your conanfile.py:
```python
    def requirements(self):
        self.requires("nbkit/1.0.0@local/stable")
```

Update your bash build file to download the binary from github:
```bash
if ! conan search nbkit/1.0.0@local/stable 2>/dev/null | grep -q "Package_ID"; then
    echo "Creating nbkit package from GitHub..."
    TMP_DIR=$(mktemp -d)
    git clone --depth 1 https://github.com/nico-bertoli/nbkit.git "$TMP_DIR/nbkit"
    conan create "$TMP_DIR/nbkit" --name=nbkit --version=1.0.0 --user=local --channel=stable
    rm -rf "$TMP_DIR"
fi
```
Link the library in CMake:
```cmake
find_package(nbkit REQUIRED)

target_link_libraries(your_target PRIVATE nbkit::nbkit)
```