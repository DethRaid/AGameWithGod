//
// Created by David on 27-Jan-16.
//

#include "gl_vertex_buffer.h"

gl_vertex_buffer::gl_vertex_buffer() {
    glGenVertexArrays(1, &gl_vao_name);
    glBindVertexArray(gl_vao_name);
    glGenBuffers(1, &gl_name);
}

void gl_vertex_buffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, gl_name);
    glBindVertexArray(gl_vao_name);
    is_bound = true;
}

void gl_vertex_buffer::upload_data(float *data, int num_elements) {
    if(!is_bound) {
        bind();
    }

    glBufferData(GL_ARRAY_BUFFER, num_elements * sizeof(float), data, GL_STATIC_DRAW);
}

GLuint gl_vertex_buffer::get_gl_name() {
    return gl_name;
}
