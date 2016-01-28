//
// Created by David on 27-Jan-16.
//

#ifndef AGAMEWITHGOD_GL_TEXTURE_H
#define AGAMEWITHGOD_GL_TEXTURE_H

#include "../glad/glad.h"

/*!
 * \brief A texture managed by OpenGL
 */
class gl_texture {
public:
    gl_texture();

    /*!
     * \brief Binds this texture to the specified texture unit
     *
     * \param texture_unit The texture unit to bind this texture to
     */
    void bind(GLuint texture_unit);

    void set_data();
private:
    GLuint gl_name;
    bool is_bound;
    GLuint current_texture_unit;
};


#endif //AGAMEWITHGOD_GL_TEXTURE_H
