//
// Created by David on 29-Jan-16.
//

#include "renderer.h"

void renderer::render(renderable &renderable) {
    shader_program & needed_shader = renderable.get_shader();

    if(needed_shader != cur_shader) {
        use_shader(needed_shader);

        renderable.upload_uniforms();
    }

    renderable.render();
}

void renderer::use_shader(shader_program &shader) {
    cur_shader = shader;
    cur_shader.bind();

    cur_shader.set_uniform("view_matrix", cur_view_matrix);
    cur_shader.set_uniform("view_matrix", cur_projection_matrix);
}
