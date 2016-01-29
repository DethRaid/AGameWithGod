//
// Created by David on 28-Jan-16.
//

#include "player.h"

player::player() : player_cam(75f, 16.0f / 9.0f, 0.01f, 1000f) {

}

camera &player::get_camera() {
    return player_cam;
}
