//
// Created by David on 26-Jan-16.
//

#include <easylogging++.h>

#include "sdl_window.h"
#include "glad/glad.h"

bool check_sdl_error() {
#ifndef NDEBUG
    const char *error = SDL_GetError();
    if(*error != '\0') {
        return true;
    }
#endif
    return false;
}

/*
 * constructors for my pretty exception
 */

sdl_exception::sdl_exception(const sdl_exception &other) {
    message << other.message.str();
}

sdl_exception::sdl_exception(int line, std::string file_name) {
    message << "SDL Error";

    const char *error = SDL_GetError();
    if(*error != '\0') {
        message << ":" << error;
    }

    message << "\nAt file " << file_name << "(" << line << ")";
}

sdl_exception::sdl_exception(int err_code, int line, std::string file_name) {
    message << "SDL Error: " << err_code;

    const char *error = SDL_GetError();
    if(*error != '\0') {
        message  << ": " << error;
    }

    message << "\nAt file " << file_name << "(" << line << ")";
}

sdl_exception::sdl_exception(int err_code, std::string msg, int line, std::string file_name) {
    message << "SDL Error: " << err_code;

    const char *error = SDL_GetError();
    if(*error != '\0') {
        message  << ": " << error;
    }

    message << "\nAt file " << file_name << "(" << line << ")";

    if(!msg.empty()) {
        message << "\nAdditional info: " << msg;
    }
}

const char *sdl_exception::what() {
    return message.str().c_str();
}

sdl_window::sdl_window() {
    // Initialize SDL
    int error_code = SDL_Init(SDL_INIT_VIDEO);

    if(error_code < 0) {
        throw sdl_exception(error_code, __LINE__, __FILE__);
    }

    LOG(INFO) << "Initialized SDL video\n";

    SDL_GL_LoadLibrary(NULL);

    LOG(INFO) << "Loaded SDL GL library\n";

    // Create the OpenGL context
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Try creating a window
    window = SDL_CreateWindow("A Game With God", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(check_sdl_error()) {
        throw sdl_exception(__LINE__, __FILE__);
    }

    LOG(INFO) << "Initialized window\n";

    /* Create our opengl context and attach it to our window */
    context = SDL_GL_CreateContext(window);
    if(check_sdl_error()) {
        throw sdl_exception(__LINE__, __FILE__);
    }

    LOG(INFO) << "Created OpenGL context\n";

    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);

    gladLoadGLLoader(SDL_GL_GetProcAddress);

    LOG(INFO) << "Vendor:   " << glGetString(GL_VENDOR) <<"\n";
    LOG(INFO) << "Renderer: " << glGetString(GL_RENDERER) <<"\n";
    LOG(INFO) << "Version:  " << glGetString(GL_VERSION) <<"\n";
}

sdl_window::~sdl_window() {
    SDL_Quit();
}

void sdl_window::end_frame() {
    SDL_GL_SwapWindow(window);

    LOG(TRACE) << "Ended frame\n";
}

SDL_GLContext &sdl_window::get_context() {
    return context;
}

bool sdl_window::should_close() {
    return should_window_close;
}

void sdl_window::start_frame() {
    while(SDL_PollEvent(&event) != 0) {
        if(event.type == SDL_QUIT) {
            should_window_close = true;
        }
    }

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    LOG(TRACE) << "Starting frame\n";
}
