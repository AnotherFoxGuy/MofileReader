from conans import ConanFile, CMake, tools
import os

class MofilereaderConan(ConanFile):
    name = "MofileReader"
    version = "1.0.0"
    license = "MIT"
    url = "https://github.com/AnotherFoxGuy/conan-MofileReader/"
    description = "This API lets you read .mo-Files and use their content just as you would do with GNUs gettext."
    settings = "os", "compiler", "build_type", "arch"
    #options = {"shared": [True, False]}
    #default_options = "shared=False"
    generators = "cmake"
    exports_sources = "include*", "src*", "CMakeLists.txt"


    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
