//
// Created by David on 27-Jan-16.
//

#ifndef AGAMEWITHGOD_GL_CONTEXT_H
#define AGAMEWITHGOD_GL_CONTEXT_H

#include <SDL2/SDL.h>

/*!
 * \brief Holds information about the current OpenGL context and has a few methods to manipulate the current OpenGL
 * context
 */
class gl_context {
public:
    /*!
     * \brief Initializes this object with a new OpenGL context fresh from SDL!
     *
     * \param window The SDL window to create the OpenGL context within
     */
    gl_context(SDL_Window * window);
private:
    SDL_GLContext sdl_context;

    int gl_version_major;
    int gl_version_minor;

};


#endif //AGAMEWITHGOD_GL_CONTEXT_H
