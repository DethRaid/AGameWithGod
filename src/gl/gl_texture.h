//
// Created by David on 27-Jan-16.
//

#ifndef AGAMEWITHGOD_GL_TEXTURE_H
#define AGAMEWITHGOD_GL_TEXTURE_H

#include <string>

#include "../glad/glad.h"

/*!
 * \brief A texture managed by OpenGL
 */
class gl_texture {
public:
    /*!
     * \brief Creates an empty texture, suitable for use in a framebuffer
     *
     * \param width The width, in pixels, of the new texture
     * \param height The height, in pixels, of the new texture
     * \param alpha If true, the texture is created with an alpha channel. If false, there's no alpha
     */
    gl_texture(GLuint width, GLuint height, bool alpha);

    /*!
     * \brief Creates a texture from the given source, suitable for use in texturing a mesh
     */
    gl_texture(std::string filename);

    /*!
     * \brief Binds this texture to the specified texture unit
     *
     * \param texture_unit The texture unit to bind this texture to
     */
    void bind(GLuint texture_unit);

    void set_data();

    GLuint get_gl_name();
private:
    GLuint gl_name;
    bool is_bound;
    GLuint current_texture_unit;
};


#endif //AGAMEWITHGOD_GL_TEXTURE_H
