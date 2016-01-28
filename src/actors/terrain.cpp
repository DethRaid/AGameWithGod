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

    buffer.upload_data(terrain_vertices);

    generate_index_buffer();
}

void terrain::generate_index_buffer() {
    std::vector<unsigned int> indices;
    for(unsigned int y = 0 ; y < num_vertices_deep - 1; y++) {
        if( y > 0) {
            // Add a degenerate vertex
            indices.push_back(y * num_vertices_deep);
        }

        for(unsigned int i = 0; i < num_vertices_wide; i++) {
            indices.push_back(i + y);
            indices.push_back(i + y + num_vertices_wide);
        }

        if( y < num_vertices_deep - 2) {
            // Add a degenerate vertex
            indices.push_back(((y * 1) * num_vertices_deep) + num_vertices_wide - 1);
        }
    }

    buffer.set_indices(indices);
}

void terrain::render() {
    buffer.draw();
}
