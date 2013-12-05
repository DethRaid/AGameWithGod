#pragma once
#include "Shader.h"
class Shaders
{
public:
	static void init();
	static Shader& getDiffuse() {return diffuse;};
	static Shader& getTerrain() {return terrain;};
	static Shader& getEmit()	{return emit;};
private:
	static Shader diffuse;
	static Shader terrain;
	static Shader emit;
};

