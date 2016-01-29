//
// Created by David on 28-Jan-16.
//

#ifndef AGAMEWITHGOD_PLAYER_H
#define AGAMEWITHGOD_PLAYER_H

#include <GL/glm/glm.hpp>
#include "camera.h"

/*!
 * \brief The player in A Game With God
 *
 * Really, the player is just a camera (and eventually an arm). This class doesn't provide a render method (until I add
 * in the arm) so there's just the get_camera method
 */
class player {
public:
    player();

    camera & get_camera();

private:
    camera player_cam;
};


#endif //AGAMEWITHGOD_PLAYER_H
