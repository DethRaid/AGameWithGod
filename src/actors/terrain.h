//
// Created by David on 27-Jan-16.
//

#ifndef AGAMEWITHGOD_TERRAIN_H
#define AGAMEWITHGOD_TERRAIN_H

#define GLM_SWIZZLE
#include <gl/glm/glm.hpp>

#include "../gl/mesh.h"
#include "../interfaces/renderable.h"
#include "shader_program.h"

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
    void set_lushness(float new_lushness);

    /*!
     * \brief Renders the terrain
     */
    virtual void render();

private:
    mesh buffer;

    unsigned int num_vertices_wide;
    unsigned int num_vertices_deep;

    float terrain_width;   //! In world units
    float terrain_depth;   //! In world units
    float terrain_height;  //! In world units

    float world_units_per_texture_tile;

    float lushness;

    glm::vec3 terrain_origin;

    shader_program terrain_shader;

    /*!
     * \brief Generates the vertex array of all the terrain vertices, sending them to the terrain's vertex buffer
     */
    void generate_terrain_vertices();
    void load_terrain_shaders();
    void load_terrain_textures();

    void generate_index_buffer();
};


#endif //AGAMEWITHGOD_TERRAIN_H
