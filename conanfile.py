from conans import ConanFile


class MofilereaderConan(ConanFile):
    name = "MofileReader"
    version = "1.1.0"
    license = "MIT"
    url = "https://github.com/AnotherFoxGuy/MofileReader/"
    description = "This API lets you read .mo-Files and use their content just as you would do with GNUs gettext."
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "include*"

    def package(self):
        self.copy("*.hpp", "include", "include")
