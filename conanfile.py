from conans import ConanFile, CMake

class SomePackage(ConanFile):
    name = "Chess AI"
    version = "1.0.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    requires = "sfml/2.5.1", "gtest/cci.20210126"

    def configure_cmake(self):
        cmake = CMake(self)
        # put definitions here so that they are re-used in cmake between
        # build() and package()
        cmake.definitions["CONAN_CMAKE_CXX_COMPILER_VERSION"] = 12.0

        cmake.configure()
        return cmake

    def build(self):
        if self.settings.os == "Windows":
            print("Windows has not been tested, feel free to try build it on your own and create a PR :)")
            return
            # do some special windows build commands

        cmake = self.configure_cmake()
        cmake.build()

        # run unit tests after the build
        cmake.test()

    def install():
         pass

    def package(self):
        cmake = self.configure_cmake()
        cmake.install()
