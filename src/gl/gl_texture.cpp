//
// Created by David on 27-Jan-16.
//

#include "gl_texture.h"

gl_texture::gl_texture(GLuint width, GLuint height, bool alpha) {
    glGenTextures(1, &gl_name);

    glBindTexture(GL_TEXTURE_2D, gl_name);

    glTexImage2D(GL_TEXTURE_2D, 0, alpha ? GL_RGB : GL_RGBA, width, height, 0, alpha ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

GLuint gl_texture::get_gl_name() {
    return gl_name;
}
