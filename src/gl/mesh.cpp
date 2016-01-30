//
// Created by David on 27-Jan-16.
//

#include "mesh.h"

mesh::mesh() {
    glGenVertexArrays(1, &gl_vao_name);
    glBindVertexArray(gl_vao_name);
    glGenBuffers(1, &gl_name);
    glGenBuffers(1, &gl_element_buffer_name);
}

void mesh::bind_all() {
    glBindBuffer(GL_ARRAY_BUFFER, gl_name);
    glBindVertexArray(gl_vao_name);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_element_buffer_name);
}

void mesh::upload_data(std::vector<vertex> vertices) {
    bind_all();

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * 12 * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Pointer for positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);

    // Pointer for normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));

    // Pointer for texture coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(6 * sizeof(float)));
}

GLuint mesh::get_gl_name() {
    return gl_name;
}

void mesh::set_indices(std::vector<unsigned int> indices) {
    bind_all();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    num_indices = indices.size();
}

void mesh::draw() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_element_buffer_name);

    glDrawElements(GL_TRIANGLE_STRIP, num_indices, GL_UNSIGNED_INT, (void*)0);
}
