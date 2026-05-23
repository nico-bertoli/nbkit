from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout
from conan.tools.files import copy
import os

class NbkitConan(ConanFile):
    
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "CMakeLists.txt", "src/*", "include/nbkit/*", "tests/*"

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        self.requires("magic_enum/0.8.0")

    def build_requirements(self):
        self.test_requires("gtest/1.15.0")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_TESTING"] = "ON" 
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["nbkit"]
        self.cpp_info.set_property("cmake_file_name", "nbkit")
        self.cpp_info.set_property("cmake_target_name", "nbkit::nbkit")