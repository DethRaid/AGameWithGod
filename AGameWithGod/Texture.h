#pragma once
#include "stdafx.h"

class Texture
{
public:
	GLuint glName;
	std::string sName;
	GLubyte *pixels;
	int x, y;
};

