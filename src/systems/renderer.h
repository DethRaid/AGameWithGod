//
// Created by David on 29-Jan-16.
//

#ifndef AGAMEWITHGOD_RENDERER_H
#define AGAMEWITHGOD_RENDERER_H

#include <gl/glm/glm.hpp>
#include "../interfaces/renderable.h"
#include "../gl/shader_program.h"
#include "../actors/camera.h"
#include "../gl/framebuffer.h"

/*!
 * \brief A class to handle global renderer stuff, like the current camera matrices, current shader, and whatever else
 */
class renderer {
public:
    /*!
     * \brief Initialized the OpenGL context, enabling everything we'll need
     */
    renderer();

    /*!
     * \brief Renders the given renderable thing.
     *
     * First gets its shader, then uploads the view and projection matrices to that shader (if that shader isn't the
     * current shader). If the renderable's shader isn't the current shader, it tells the renderable to upload its
     * uniforms tot he current shader. Then tells the renderable to render itself.
     */
    void render(renderable & renderable);

    /*!
     * \brief Sets the given framebuffer as the active framebuffer
     *
     * \param buffer_to_use The framebuffer to render to
     */
    void use_framebuffer(framebuffer & buffer_to_use);

    /*!
     * \brief Sets the current camera as the active camera
     *
     * Saves the camera, then sends its view and projection matrices to the current shader
     *
     * \param cam_to_use The camera to use for future renders
     */
    void use_camera(camera & cam_to_use);

    /*!
     * \brief Sets up the current frame, doing things such as clearing the color and depth buffers
     */
    void begin_frame();

    /*!
     * \brief Ends the current grame, flushing OpenGL and whatnot
     */
    void end_frame();

    /*!
     * \brief Begins the final render.
     *
     * Tells OpenGL to draw the the screen, not an internal framebuffer.
     */
    void begin_final();

private:
    camera & cur_camera;

    shader_program & cur_shader;

    framebuffer & cur_framebuffer;

    void upload_camera_matrices() const;

    /*!
     * \brief Sets the given shader as the current shader
     *
     * Binds the shader to OpenGL and uploads the current view and projection matrices.
     *
     * Shaders should only be changed when the currently rendered mesh changes.
     *
     * \param shader The shader program to use
     */
    void use_shader(shader_program &shader);
};


#endif //AGAMEWITHGOD_RENDERER_H

