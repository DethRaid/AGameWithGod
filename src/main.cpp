#include <iostream>
#include <SDL2/SDL_main.h>
#include <easylogging++.h>

#include "sdl_window.h"
#include "glad/glad.h"
#include "actors/terrain.h"
#include "actors/player.h"
#include "systems/renderer.h"
#include "gl/framebuffer.h"

using namespace std;

INITIALIZE_EASYLOGGINGPP

void initialize_logging() {
    // Configure the logger
    el::Configurations conf("logging.conf");

    // Turn debug and trace off in release builds
#ifndef NDEBUG
    conf.parseFromText("*DEBUG:\n ENABLED=false");
    conf.parseFromText("*TRACE:\n ENABLED=false");
#endif

    el::Loggers::reconfigureAllLoggers(conf);
}

int main(int argc, char* argv[]) {
    initialize_logging();

    sdl_window main_window;
    renderer main_renderer;
    framebuffer gbuffer(640, 480, {3, 4});

    terrain main_terrain;

    player main_player;
    camera main_camera = main_player.get_camera();

    main_renderer.use_camera(main_camera);

    while(!main_window.should_close()) {
        // Check for user input
        main_window.check_events();

        // Process the input, update AI and whatnot
        // TODO

        // Begin rendering
        main_renderer.begin_frame();

        // Begin rendering to the gbuffer
        main_renderer.use_framebuffer(gbuffer);

        main_renderer.render(main_terrain);

        // Render to the lighting buffer
        // TODO

        // Render to the screen
        main_renderer.begin_final();

        // Cleanup and whatnot
        main_renderer.end_frame();

        main_window.end_frame();
    }

    return 0;
}