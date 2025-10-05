from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.scm import Git


class batterychargerRecipe(ConanFile):
    name = "batterycharger"
    version = "0.0.1"
    package_type = "application"

    # Optional metadata
    license = "GPL-2.0"
    author = "tomatenkuchen"
    url = "https://github.com/tomatenkuchen/batterycharger"
    description = "power management device for small PV, batteries and power unit inputs"
    topics = ("lipo","PV", "power management", "embedded")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*"

    def set_version(self):
        git = Git(self, self.recipe_folder)
        self.version = git.run("describe --tags").split('-')[0]
        self.hash = git.run("rev-parse HEAD")

    def requirements(self):
        self.tool_requires("cmake/4.1.0")
        self.tool_requires("ninja/1.13.1")
        # self.tool_requires("cppcheck/2.18.3")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self, generator="Ninja")
        tc.cache_variables["CONAN_PROJECT_NAME"] = str(self.name)
        tc.cache_variables["CONAN_PROJECT_VERSION"] = str(self.version)
        tc.cache_variables["CONAN_PROJECT_DESCRIPTION"] = str(self.description)
        tc.cache_variables["CONAN_PROJECT_GIT_HASH"] = str(self.hash)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    

    
