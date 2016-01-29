//
// Created by David on 28-Jan-16.
//

#ifndef AGAMEWITHGOD_CAMERA_H
#define AGAMEWITHGOD_CAMERA_H

#include <GL/glm/glm.hpp>

/*!
 * \brief A camera the world can be rendered through
 */
class camera {
public:
    /*!
     * \brief Constructs a new camera with the given defaults
     *
     * \param field_of_view The field of view of the new camera, measured in degrees
     * \param near_clip_plane How close objects can be to the camera before they're no longer rendered
     * \param far_clip_plane How far things can be from the camera before they're no longer rendered
     */
    camera(float field_of_view, float aspect_ratio, float near_clip_plane, float far_clip_plane);

    /*!
     * \brief Sets the position of the camera to the new position
     *
     * \param new_position The desired position of the camera
     */
    void set_position(glm::vec3 new_position);

    /*!
     * \brief Sets this camera's yaw to the specified value
     *
     * \param new_yaw The desired yaw of the camera
     */
    void set_yaw(float new_yaw);

    /*!
     * \brief Sets this camera's pitch to the specified value
     *
     * \param new_pitch The desired pitch of the camera
     */
    void set_pitch(float new_pitch);

    /*!
     * \brief Retrieves the camera's view matrix
     *
     * \return The camera's view matrix
     */
    glm::mat4 get_view_matrix();

    /*!
     * \brief Retrieves the camera's projection matrix
     *
     * \return The camera's projection matrix
     */
    glm::mat4 get_projection_matrix();
private:
    glm::vec3 position;
    float pitch;
    float yaw;
    float field_of_view;
    float aspect_ratio;
    float near_clip_plane;
    float far_clip_plane;

    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;

    void recalc_view_matrix();
    void recalc_projection_matrix();
};


#endif //AGAMEWITHGOD_CAMERA_H
