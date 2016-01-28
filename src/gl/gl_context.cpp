//
// Created by David on 27-Jan-16.
//

#include "gl_context.h"

gl_context::gl_context(SDL_Window * window) {
   gl_context = SDL_GL_CreateContext(window);
}
