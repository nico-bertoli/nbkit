from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout
from conan.tools.files import copy
import os

class NbkitConan(ConanFile):
    name = "nbkit"
    version = "1.0.0"
    description = "A set of common classes that can be shared across projects"
    license = "MIT" 
    author = "Nicolò Bertoli <nicobertoli.1999@gmail.com>"
    url = "https://github.com/nico-bertoli/nbkit"
    
    settings = "os", "compiler", "build_type", "arch"

    # fPIC = Position Independent Code, t is a requirement on Linux for creating shared Libraries
    # on windows it's not needed and can cause issues
    options = {"shared": [True, False], "fpic": [True, False]}
    default_options = {"shared": False, "fpic": True}

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fpic

    def layout(self):
        cmake_layout(self)

    def build_requirements(self):
        self.test_requires("gtest/1.15.0")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_TESTING"] = "ON" 
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def export_sources(self):
        copy(self, "CMakeLists.txt", self.recipe_folder, self.export_sources_folder)
        copy(self, "nbkit/*", self.recipe_folder, self.export_sources_folder)
        copy(self, "tests/*", self.recipe_folder, self.export_sources_folder)

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