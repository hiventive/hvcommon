from conans import ConanFile, CMake, tools
from conans.util import files
import yaml

class HVCommonConan(ConanFile):
    name = str(yaml.load(tools.load("settings.yml"))['conan']['name'])
    version = yaml.load(tools.load("settings.yml"))['project']['version']
    license = "MIT"
    author = "Hiventive"
    url = "https://github.com/hiventive/hvcommon"
    description = "Common utils"
    settings = "cppstd", "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False], "fPIE": [True, False]}
    default_options = "shared=False", "fPIC=False", "fPIE=False"
    generators = "cmake"
    no_copy_source = True # TODO: remove that (GLOB_RECURSIVE issue)
    exports = "settings.yml"
    exports_sources = "src/*", "CMakeLists.txt", "cmake/*"
    requires = "gtest/1.8.0@hiventive/stable", \
               "spdlog/0.16.3@hiventive/stable", \
               "cci/1.0.0@hiventive/stable"

    def _configure_cmake(self):
        cmake = CMake(self)
        if self.settings.os != "Windows":
            cmake.definitions["CMAKE_POSITION_INDEPENDENT_CODE"] = self.options.fPIC or self.options.fPIE
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["hvcommon"]
