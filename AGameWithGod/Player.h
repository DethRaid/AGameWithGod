#pragma once
#include "stdafx.h"
#include "Actor.h"
#include "Camera.h"
#include "Shaders.h"

class Player : public Actor
{
public:
	Player();
	~Player();

	/*This is how we should deal with player speed*/
	float getSpeed() {return 1.0f;};

	/*Loads the current view transform, from the camera relative to the player*/
	void loadView();
	void update();

	void render();
	void fire();

	void giveXP( int XP ) {xp += XP; if( xp > nextLevelXP ){ level++; nextLevelXP *= 2; }};

	Transform& getTransform() {return transform;};
private:
	bool shooting, firstShot;
	int xp, level, nextLevelXP;
	Camera camera;
	Vector3 projectilePos, projectileDir, projectileStart;
};

