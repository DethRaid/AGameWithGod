//
// Created by David on 29-Jan-16.
//

#include <stdexcept>
#include "framebuffer.h"

framebuffer_color_attachment::framebuffer_color_attachment(unsigned int width, unsigned int height, bool alpha) {
    glGenTextures(1, &gl_name);

    glBindTexture(GL_TEXTURE_2D, gl_name);

    glTexImage2D(GL_TEXTURE_2D, 0, alpha ? GL_RGB : GL_RGBA, width, height, 0, alpha ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

GLuint framebuffer_color_attachment::get_gl_name() {
    return gl_name;
}

framebuffer_depth_attachment::framebuffer_depth_attachment(unsigned int width, unsigned int height, unsigned int num_bits) {
    glGenTextures(1, &gl_name);

    glBindTexture(GL_TEXTURE_2D, gl_name);

    GLuint depth_component_thing;

    switch(num_bits) {
        case 16:
            depth_component_thing = GL_DEPTH_COMPONENT16;
            break;
        case 24:
            depth_component_thing = GL_DEPTH_COMPONENT24;
            break;
        case 32:
            depth_component_thing = GL_DEPTH_COMPONENT32;
            break;
        default:
            throw std::invalid_argument("num_bits must be 16, 24, or 32");
    }

    glTexImage2D(GL_TEXTURE_2D, 0, depth_component_thing, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

GLuint framebuffer_depth_attachment::get_gl_name() {
    return gl_name;
}

framebuffer::framebuffer(GLuint width, GLuint height, std::vector<unsigned int> attachments) :
        depth_attachment(width, height, 24) {
    glGenFramebuffers(1, &gl_name);
    glBindFramebuffer(GL_FRAMEBUFFER, gl_name);

    GLenum drawbuffers[attachments.size() + 1];

    for(unsigned int i = 0; i < attachments.size(); i++) {
        framebuffer_color_attachment new_attachment(width, height, attachments[i] == 4);

        color_attachments.push_back(new_attachment);

        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, new_attachment.get_gl_name(), 0);
        drawbuffers[i] = GL_COLOR_ATTACHMENT0 + i;
    }

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_attachment.get_gl_name(), 0);
    drawbuffers[attachments.size()] = GL_DEPTH_ATTACHMENT;

    glDrawBuffers(attachments.size(), drawbuffers);
}

void framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, gl_name);
    glViewport(0, 0, width, height);
}

framebuffer_color_attachment &framebuffer::get_color_attachment(unsigned int index) {
    return color_attachments[index];
}

framebuffer_depth_attachment &framebuffer::get_depth_attachment() {
    return depth_attachment;
}

bool framebuffer::operator!=(const framebuffer &other) const {
    return gl_name != other.gl_name;
}
