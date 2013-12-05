#pragma once
#include "Actor.h"
#include "Mesh.h"
#include "Shaders.h"

class Temple :
	public Actor
{
public:
	Temple();
	~Temple();

	void init();
	void render();
private:
	GLuint texture;
	Mesh mesh;
};

