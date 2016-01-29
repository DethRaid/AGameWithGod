//
// Created by David on 27-Jan-16.
//

#ifndef AGAMEWITHGOD_RENDERABLE_H
#define AGAMEWITHGOD_RENDERABLE_H

#include "shader_program.h"

/*!
 * \brief Simple interfcae for things that are renderable
 */
class renderable {
public:
    /*!
     * Renders this object however is best
     */
    virtual void render() = 0;

    /*!
     * \brief Uploads this renderable's material's variables to its shader
     */
    virtual void upload_uniforms() = 0;

    /*!
     * \brief Returns this renderable's shader
     *
     * \return This renderable's shader
     */
    shader_program & get_shader();

private:
    shader_program my_shader;
};


#endif //AGAMEWITHGOD_RENDERABLE_H
