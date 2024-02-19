from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class BebraCraftRecipe(ConanFile):
    name = "BebraCraft"
    version = "0.1-pre-alpha"
    package_type = "application"

    # Optional metadata
    license = "MIT"
    author = "6yntar05"
    url = "https://github.com/6yntar05/BebraCraft"
    description = "Students laboratory work. OpenGL C++ Minecraft (not)clone "
    topics = ("minecraft", "c++", "opengl")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*"

    # Deps
    requires = "sdl/2.28.5", "freetype/2.13.2"#, "glm/0.9.9.8"

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    

    
