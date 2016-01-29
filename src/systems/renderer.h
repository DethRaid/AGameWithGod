//
// Created by David on 29-Jan-16.
//

#ifndef AGAMEWITHGOD_RENDERER_H
#define AGAMEWITHGOD_RENDERER_H

#include <gl/glm/glm.hpp>
#include "../interfaces/renderable.h"
#include "../gl/shader_program.h"

/*!
 * \brief A class to handle global renderer stuff, like the current camera matrices, current shader, and whatever else
 */
class renderer {
public:
    renderer();

    /*!
     * \brief Renders the given renderable thing.
     *
     * First gets its shader, then uploads the view and projection matrices to that shader (if that shader isn't the
     * current shader). If the renderable's shader isn't the current shader, it tells the renderable to upload its
     * uniforms tot he current shader. Then tells the renderable to render itself.
     */
    void render(renderable & renderable);
private:
    glm::mat4 cur_view_matrix;
    glm::mat4 cur_projection_matrix;

    shader_program & cur_shader;

    void use_shader(shader_program &shader);
};


#endif //AGAMEWITHGOD_RENDERER_H
