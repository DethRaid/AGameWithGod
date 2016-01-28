//
// Created by David on 27-Jan-16.
//

#ifndef AGAMEWITHGOD_GL_VERTEX_BUFFER_H
#define AGAMEWITHGOD_GL_VERTEX_BUFFER_H

#include <vector>

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
 * A vertex buffer also contains the index buffer for itself. So actually, a vertex buffer is a full mesh. All well.
 *
 * It's worth noting that positions are always bound to location 0, normals are always location 1, and texture
 * coordinates are always location 2. Always. Write your shaders accordingly
 */
class mesh {
public:
    /*!
     * \brief Allocates a new vertex buffer on the GPU
     */
    mesh();

    /*!
     * \brief Uploads the given data to this vertex buffer
     *
     * \param vertices An array of the vertices to upload
     */
    void upload_data(std::vector<vertex> vertices);

    /*!
     * \brief Uploads the given indices to this vertex buffer's indes buffer
     *
     * \param indices An array of the indices to upload
     */
    void set_indices(std::vector<unsigned int> indices);

    /*!
     * \brief Binds this VBO to the GL_ARRAY_BUFFER thing, allowing us to use it.
     */
    void bind_all();

    /*!
     * \brief Draws this mesh
     */
    void draw();

    /*!
     * \return The OpenGL name of this VBO
     */
    GLuint get_gl_name();
private:
    GLuint gl_name;
    GLuint gl_vao_name;
    GLuint gl_element_buffer_name;

    unsigned int num_indices;
};


#endif //AGAMEWITHGOD_GL_VERTEX_BUFFER_H
