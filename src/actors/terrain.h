//
// Created by David on 27-Jan-16.
//

#ifndef AGAMEWITHGOD_TERRAIN_H
#define AGAMEWITHGOD_TERRAIN_H

#include <gl/glm/glm.hpp>

#include "../gl/gl_vertex_buffer.h"
#include "../interfaces/renderable.h"
#include "../gl/shader.h"

/*!
 * \brief Represents the wonderfully dynamic terrain in A Game With God
 *
 * The terrain handles its shaders and everything. You just give it a "lushness" parameter, and it smoothly blends
 * between a barren desert and a lush mountain.
 */
class terrain : public renderable {
public:
    /*!
     * \brief Generates the actual terrain, creating a VBO for its vertices, generating the heightmap, loading all my
     * terrain textures, loading its shaders, etc.
     */
    terrain();

    /*!
     * \brief Sets the lushness of the terrain to the desired value
     *
     * Actually saves the lushness to be sent to the terrain shader at render time
     *
     * \param new_lushness The desired lushness of the terrain
     */
    void set_lushness(unsigned float new_lushness);

    /*!
     * \brief Renders the terrain
     */
    virtual void render();

private:
    gl_vertex_buffer buffer;

    unsigned int num_vertices_wide;
    unsigned int num_vertices_deep;

    unsigned float terrain_width;
    unsigned float terrain_depth;
    unsigned float terrain_height;

    unsigned float world_units_per_texture_tile;

    unsigned float lushness;

    glm::vec3 terrain_origin;

    shader terrain_shader;

    /*!
     * \brief Generates the vertex array of all the terrain vertices, sending them to the terrain's vertex buffer
     */
    void generate_terrain_vertices();
    void load_terrain_shaders();
    void load_terrain_textures();
};


#endif //AGAMEWITHGOD_TERRAIN_H