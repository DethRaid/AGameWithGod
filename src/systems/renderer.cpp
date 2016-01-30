//
// Created by David on 29-Jan-16.
//

#include "renderer.h"

renderer::renderer() : cur_camera(), cur_shader(), cur_framebuffer() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
}

void renderer::render(renderable &renderable) {
    shader_program & needed_shader = renderable.get_shader();

    if(needed_shader != cur_shader) {
        use_shader(needed_shader);

        renderable.upload_uniforms();
    }

    renderable.render();
}

void renderer::use_framebuffer(framebuffer & buffer_to_use) {
    if(cur_framebuffer != buffer_to_use) {
        cur_framebuffer = buffer_to_use;

        cur_framebuffer.bind();
    }
}

void renderer::use_shader(shader_program &shader) {
    cur_shader = shader;
    cur_shader.bind();

    upload_camera_matrices();
}

void renderer::upload_camera_matrices() const {
    cur_shader.set_uniform("view_matrix", cur_camera.get_view_matrix());
    cur_shader.set_uniform("view_matrix", cur_camera.get_view_matrix());
}

void renderer::use_camera(camera &cam_to_use) {
    cur_camera = cam_to_use;

    upload_camera_matrices();
}

void renderer::begin_frame() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void renderer::end_frame() {
    glFlush();
}

void renderer::begin_final() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
