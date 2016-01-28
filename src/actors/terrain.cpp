//
// Created by David on 27-Jan-16.
//

#include <vector>

#include "terrain.h"

terrain::terrain() {
    generate_terrain_vertices();
}

void terrain::generate_terrain_vertices() {
    std::vector<vertex> terrain_vertices;

    glm::vec3 position_ratio(
            terrain_width / num_vertices_wide,
            0,
            terrain_depth / num_vertices_deep
    );

    glm::vec2 texcoord_ratio(
            world_units_per_texture_tile / position_ratio.x,
            world_units_per_texture_tile / position_ratio.z
    );

    for(int i = 0; i < num_vertices_deep * num_vertices_wide; i++ ) {
        glm::vec3 position((i % num_vertices_wide), 0, (i / num_vertices_deep));
        position *= position_ratio;

        glm::vec2 texcoord(position.x, position.z);
        texcoord *= texcoord_ratio;

        terrain_vertices.push_back({position, glm::vec3(0), texcoord});
    }

    buffer.upload_data((float *)(terrain_vertices.data()), terrain_vertices.size() * 8);
}
