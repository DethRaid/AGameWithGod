#pragma once
#include "Actor.h"
#include "Shaders.h"
class Tree : public Actor
{
public:
	Tree();
	Tree( Vector3 );
	~Tree();
	void init();
	void render();
	GLuint getTexture() {return texture;};
	void hide() {canDraw = false;};
	void show() {canDraw = true;};
private:
	GLuint texture;
	bool canDraw;
};

