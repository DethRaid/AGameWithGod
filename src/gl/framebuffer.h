//
// Created by David on 29-Jan-16.
//

#ifndef AGAMEWITHGOD_FRAMEBUFFER_H
#define AGAMEWITHGOD_FRAMEBUFFER_H

#include <vector>

#include "../glad/glad.h"
#include "gl_texture.h"

/*!
 * \brief A color attachment for a framebuffer. Basically a texture, but this code shouldn't be in gl_texture.
 */
class framebuffer_color_attachment {
public:
    /*!
     * \brief Creates a new framebuffer color attachment with the given width and height
     *
     * \param width The width, in pixels, of the texture
     * \param height The height, in pixels, of the texture
     * \param alpha If true, the attachment will have an alpha channel. If false, the texture will have no alpha channel
     */
    framebuffer_color_attachment(unsigned int width, unsigned int height, bool alpha);

    /*!
     * \brief Gets the OpenGL name for this texture
     *
     * \param The OpenGL name for this texture
     */
    GLuint get_gl_name();
private:
    GLuint gl_name;
};

class framebuffer_depth_attachment {
public:
    /*!
     * \brief Creates a new framebuffer depth attachment
     *
     * \param width The width, in pixels, of the texture
     * \param height The height, in pixels, of the texture
     * \param num_bits Either 16, 24, or 32.
     */
    framebuffer_depth_attachment(unsigned int width, unsigned int height, unsigned int num_bits);

    GLuint get_gl_name();
private:
    GLuint gl_name;
};

/*!
 * \brief A class to represent a framebuffer
 *
 * Framebuffers have a size and anumber of attachments. This handles all of that
 */
class framebuffer {
public:
    /*!
     * \brief Initializes the framebuffer with the given width, height, and number of attachments
     *
     * \param width The width, in pixels, of this framebuffer
     * \param height The heighs, in pixels, of this framebuffer
     * \param attachments A description of the attachments to give this framebuffer. The number of elements in the
     * vector is the number of attachments you want, and the number at each index is the number of channels that
     * attachment should have.
     */
    framebuffer(GLuint width, GLuint height, std::vector<unsigned int> attachments);

    /*!
     * \brief Binds this framebuffer as tha active framebuffer
     *
     * Binds this framebuffer to OpenGL and sets the OpenGL viewport to this framebuffer's viewport
     */
    void bind();

    /*!
     * \brief Gets the color attachment at the given index
     *
     * \param index The index of the color attachment to retrieve
     *
     * \return The requested color attachment if available
     */
    framebuffer_color_attachment & get_color_attachment(unsigned int index);

    /*!
     * \brief Retrieves the depth attachment
     *
     * \return The depth attachment
     */
    framebuffer_depth_attachment & get_depth_attachment();

    /*!
     * \brief Determines if this framebuffer is equal to another framebuffer
     *
     * Compares the gl_name of each framebuffer
     */
    bool operator!=(const framebuffer & other) const;

private:
    GLuint width;
    GLuint height;

    GLuint gl_name;

    std::vector<framebuffer_color_attachment> color_attachments;
    framebuffer_depth_attachment depth_attachment;
};


#endif //AGAMEWITHGOD_FRAMEBUFFER_H
