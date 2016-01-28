#include <iostream>
#include <SDL2/SDL_main.h>

#include "sdl_window.h"
#include "glad/glad.h"
#include "actors/terrain.h"

using namespace std;

int main(int argc, char* argv[]) {
    sdl_window main_window;

    terrain main_terrain;

    while(true) {
        main_terrain.render();
    }

    return 0;
}