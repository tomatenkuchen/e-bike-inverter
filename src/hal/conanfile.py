from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class batterychargerRecipe(ConanFile):
    name = "batterycharger"
    version = "0.0.1"
    package_type = "application"

    # Optional metadata
    license = "GPL v2.0"
    author = "tomatenkuchen"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "<using a ST Microelectronics B-G431B-ESC1 board to transfer power from a supply to a LiPo battery>"
    topics = ("<battery>", "<charging>", "<buck>", "<boost>")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*"

    def requirements(self):
        self.tool_requires("cmake/4.1.0")
        self.tool_requires("ninja/1.13.1")
        self.tool_requires("doxygen/1.14.0")
        self.tool_requires("cppcheck/2.18.3")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self, generator="Ninja")
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

