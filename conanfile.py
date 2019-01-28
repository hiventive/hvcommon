from conans import ConanFile, CMake, tools
from conans.util import files
import yaml

class CommonConan(ConanFile):
    name = "common"
    version = yaml.load(tools.load("settings.yml"))['project']['version']
    license = "MIT"
    author = "Hiventive"
    url = "https://github.com/hiventive/hvcommon"
    description = "Common utils"
    settings = "cppstd", "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False], "fPIE": [True, False]}
    default_options = "shared=False", "fPIC=False", "fPIE=False"
    generators = "cmake"
    exports = "settings.yml"
    exports_sources = "src/*", "CMakeLists.txt"
    requires = "gtest/1.8.0@bincrafters/stable", \
               "spdlog/0.16.3@hiventive/stable", \
               "cci/1.0.0@hiventive/stable"

    def build(self):
        cmake = CMake(self)
        files.mkdir("build")
        with tools.chdir("build"):
            if self.settings.os != "Windows":
                cmake.definitions["CMAKE_POSITION_INDEPENDENT_CODE"] = self.options.fPIC or self.options.fPIE
            cmake.configure(build_dir=".", source_dir="../")
            cmake.build(build_dir=".")
            cmake.install(build_dir=".")

        # Explicit way:
        # self.run('cmake %s/src %s' % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("HVCommon", dst="include", src="src")
        self.copy("*.h", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["common"]
