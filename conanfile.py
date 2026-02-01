from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout

class NbkitConan(ConanFile):
    
    #----------------------------- package info
    name = "nbkit"
    version = "1.0.0"
    description = "A set of common classes that can be shared across projects"
    license = "MIT" 
    author = "Nicolò Bertoli <nicobertoli.1999@gmail.com>"
    url = "https://github.com/nico-bertoli/nbkit"
    
    #----------------------------- conan setup
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"
    exports_sources = "CMakeLists.txt", "nbkit/*", "tests/*"
    
    #----------------------------- 
    def layout(self):
        cmake_layout(self)
    
    def build_requirements(self):
        self.test_requires("gtest/1.14.0")
    
    def build(self):
        cmake = CMake(self)
        cmake.configure(variables={"BUILD_TESTING": "ON"})
        cmake.build()
        cmake.test()
    
    def package(self):
        cmake = CMake(self)
        cmake.install()
    
    def package_info(self):
        self.cpp_info.libs = ["nbkit"] 
        self.cpp_info.includedirs = ["include"]
        self.cpp_info.set_property("cmake_target_name", "nbkit::nbkit")