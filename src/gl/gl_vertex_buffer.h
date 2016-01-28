//
// Created by David on 27-Jan-16.
//

#ifndef AGAMEWITHGOD_GL_VERTEX_BUFFER_H
#define AGAMEWITHGOD_GL_VERTEX_BUFFER_H

#include <GL/glm/glm.hpp>
#include "../glad/glad.h"

/*!
 * \brief Represents a single vertex
 *
 * All vertices have the same layout, which makes a lot of things way simpler. I'm not coding a general-purpose game
 * engine, I'm making a single game
 */
struct vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
};

/*!
 * \brief Represents an OpenGL VBO, providing operations to upload data to the VBO, bind it, and whatever else
 *
 * Also generates a VAO, because every VBO needs to be part of a VAO. I have one VBO per VAO, since my VBOs are always
 * interleaved, so I just generate the VAO here and treat VBOs and VAOs as one thing
 *
 * A vertex buffer also contains the
 */
class gl_vertex_buffer {
public:
    /*!
     * \brief Allocates a new vertex buffer on the GPU
     */
    gl_vertex_buffer();

    /*!
     * \brief Uploads the given data to this vertex buffer
     *
     * \param data The raw data to upload
     * \param num_elements The number of floats in the data array
     */
    void upload_data(float * data, int num_elements);

    /*!
     * \brief Binds this VBO to the GL_ARRAY_BUFFER thing, allowing us to use it.
     */
    void bind();

    /*!
     * \return The OpenGL name of this VBO
     */
    GLuint get_gl_name();
private:
    GLuint gl_name;
    GLuint gl_vao_name;
    GLuint gl_index_array_name;
    bool is_bound;
};


#endif //AGAMEWITHGOD_GL_VERTEX_BUFFER_H
