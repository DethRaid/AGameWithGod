//
// Created by David on 26-Jan-16.
//

#ifndef AGAMEWITHGOD_SDL_WINDOW_H
#define AGAMEWITHGOD_SDL_WINDOW_H

#include <SDL2/SDL.h>
#include <exception>
#include <sstream>
#include <stdexcept>

/*!
 * \brief An exception to handle SDL errors
 *
 * Will I make more granular exceptions in the future? Only time will tell
 */
class sdl_exception : public std::exception {
public:
    sdl_exception(const sdl_exception &other);

    /*!
     * \brief Constructs an error with the given SDL error code, pulling the error message from the SDL runtime
     *
     * \param err_code The error code that SDL returns
     * \param msg Any message you wish to provide
     */
    sdl_exception(int line, std::string file_name);


    /*!
     * \brief Constructs an error with the given SDL error code, pulling the error message from the SDL runtime
     *
     * \param err_code The error code that SDL returns
     * \param msg Any message you wish to provide
     */
    sdl_exception(int err_code, int line, std::string file_name);

    /*!
     * \brief Constructs an error with the given SDL error code, pulling the error message from the SDL runtime
     *
     * \param err_code The error code that SDL returns
     * \param msg Any message you wish to provide
     */
    sdl_exception(int err_code, std::string msg, int line, std::string file_name);

    /*!
     * \brief Returns the complete message of this exception
     *
     * Usually something like "SDL error <err>: <sdl_msg>\nAdditional info: <msg>
     *
     * \return The complete message of this exception
     */
    virtual const char * what();
private:
    std::stringstream message;
};

/*!
 * \brief Represents a window
 *
 * This window is essentially the parent of the OpenGL context, due to how OpenGL contexts work. It manages the
 * context's lifecycle, creating it and destroying it.
 */
class sdl_window {
public:
    /*!
     * \brief Initializes the window, creating it and showing it
     */
    sdl_window();

    /*!
     * \brief Destroys the window, shutting down SDL
     */
    ~sdl_window();

    /*!
     * \brief Ends the current frame, swapping our fancy buffers and whatnot
     */
    void end_frame();

    /*!
     * \return The OpenGL context associated with this window
     */
    SDL_GLContext & get_context();

private:
    SDL_Window *window;
    SDL_GLContext context;
};


#endif //AGAMEWITHGOD_SDL_WINDOW_H
