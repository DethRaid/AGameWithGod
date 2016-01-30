cmake_minimum_required(VERSION 3.3)
project(AGameWithGod)

include_directories(
        "C:/MinGW/include"
        "C:/MinGW/lib/gcc/mingw32/4.8.1/include/c++"
)

link_directories(
        "C:/MinGW/lib"
)

set(SOURCE_FILES src/main.cpp src/glad/glad.h src/glad/glad.c src/sdl_window.cpp src/sdl_window.h src/gl/mesh.cpp src/gl/mesh.cpp src/gl/mesh.h src/actors/terrain.cpp src/actors/terrain.h src/interfaces/renderable.cpp src/interfaces/renderable.h src/gl/shader_program.cpp src/gl/shader_program.h src/gl/gl_texture.cpp src/gl/gl_texture.h src/actors/player.cpp src/actors/player.h src/actors/camera.cpp src/actors/camera.h src/systems/renderer.cpp src/systems/renderer.h src/gl/framebuffer.cpp src/gl/framebuffer.h)
add_executable(AGameWithGod ${SOURCE_FILES})

# configure the SDL (cf. "SDL2-2.0.3\i686-w64-mingw32\lib\pkgconfig\sdl2.pc")
# C++ flags
set(SDL2_Flags "-Wl,--no-undefined -static-libgcc")
# library paths
# TODO: Set SDL_ROOT on each compiling machine
set(SDL2_ROOT     "C:/SDL2-2.0.3/i686-w64-mingw32")
set(SDL2_Includes "${SDL2_ROOT}/include")
set(SDL2_LibDir   "${SDL2_ROOT}/lib")
# imported targets for CMake (cf. https://cmake.org/Wiki/CMake/Tutorials/Exporting_and_Importing_Targets)
add_library(SDL2     STATIC IMPORTED)
add_library(SDL2main STATIC IMPORTED)
set_property(TARGET SDL2     PROPERTY IMPORTED_LOCATION "${SDL2_LibDir}/libSDL2.a")
set_property(TARGET SDL2main PROPERTY IMPORTED_LOCATION "${SDL2_LibDir}/libSDL2main.a")
# the libs to link against
# note: as always with gcc, the order is important...
set(SDL2_Libs mingw32 SDL2main SDL2 m dinput8 dxguid dxerr8 user32 gdi32 winmm imm32 ole32 oleaut32 shell32 version uuid)

# configure the project
# include the SDL flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SDL2_Flags}")
# include the SDL headers
target_include_directories(AGameWithGod SYSTEM PRIVATE ${SDL2_Includes})
# link against the SDL (and its dependencies)
target_link_libraries(AGameWithGod ${SDL2_Libs})

set_property(TARGET AGameWithGod PROPERTY CXX_STANDARD 14)
set_property(TARGET AGameWithGod PROPERTY CXX_STANDARD_REQUIRED ON)