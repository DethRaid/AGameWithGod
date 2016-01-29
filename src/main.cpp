#include <iostream>
#include <SDL2/SDL_main.h>
#include <easylogging++.h>

#include "sdl_window.h"
#include "glad/glad.h"
#include "actors/terrain.h"
#include "actors/player.h"

using namespace std;

INITIALIZE_EASYLOGGINGPP

void initialize_logging() {
    // Configure the logger
    el::Configurations conf("logging.conf");

    // Turn debug and trace off in release builds
#ifndef NDEBUG
    conf.parseFromText("*DEBUG:\n ENABLED=false");
#endif

    el::Loggers::reconfigureAllLoggers( conf );
}

int main(int argc, char* argv[]) {
    initialize_logging();

    sdl_window main_window;

    terrain main_terrain;

    player main_player;
    camera main_camera = main_player.get_camera();

    while(!main_window.should_close()) {
        main_window.start_frame();

        main_terrain.render();

        main_window.end_frame();
    }

    return 0;
}