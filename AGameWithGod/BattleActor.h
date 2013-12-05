#pragma once
#include "stdafx.h"
#include "actor.h"
#include "Globals.h"
#include "Shaders.h"
#include "Texture.h"

class BattleActor : public Actor
{
public:
	BattleActor(void);
	~BattleActor(void);
	void init();
	void buildTexture();
	void render();
	void update( BattleActor* );
	float getBlendFac() {return blendFac;};
private:
	BattleActor *target;
	GLuint texture;
	Texture humanTex, monsterTex, tex;
	//the amount that a battleACtor is Human
	float blendFac;
	float speed;
	int curFrame;
};

