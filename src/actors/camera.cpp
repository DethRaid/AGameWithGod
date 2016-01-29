//
// Created by David on 28-Jan-16.
//

#include "camera.h"
#include <gl/glm/gtc/matrix_transform.hpp>

#define PI 3.14159265f

camera::camera(float field_of_view, float aspect_ratio, float near_clip_plane, float far_clip_plane) {
    this->field_of_view = field_of_view;
    this->aspect_ratio = aspect_ratio;
    this->near_clip_plane = near_clip_plane;
    this->far_clip_plane = far_clip_plane;

    recalc_view_matrix();
    recalc_projection_matrix();
}

void camera::set_position(glm::vec3 new_position) {
    position = new_position;
    recalc_view_matrix();
}

void camera::set_yaw(float new_yaw) {
    yaw = new_yaw;
    recalc_view_matrix();
}

void camera::set_pitch(float new_pitch) {
    pitch = new_pitch;
    recalc_view_matrix();
}

glm::mat4 camera::get_view_matrix() {
    return view_matrix;
}

glm::mat4 camera::get_projection_matrix() {
    return projection_matrix;
}

void camera::recalc_view_matrix() {
    float pitch_in_radians = pitch * PI / 180.0f;
    float yaw_in_radians = yaw * PI / 180.0f;

    glm::vec3 forward(
            cos(pitch_in_radians) * sin(yaw_in_radians),
            sin(pitch_in_radians),
            cos(pitch_in_radians) * cos(yaw_in_radians)
    );

    glm::vec3 right(
            sin(yaw_in_radians - PI / 2.0f),
            0,
            cos(yaw_in_radians - PI / 2.0f)
    );

    glm::vec3 up = glm::cross(right, forward);

    view_matrix = glm::lookAt(position, position + forward, up);
}

void camera::recalc_projection_matrix() {
    projection_matrix = glm::perspective(field_of_view, aspect_ratio, near_clip_plane, far_clip_plane);
}
