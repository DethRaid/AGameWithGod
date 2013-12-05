#pragma once
#include "stdafx.h"
#include "Texture.h"

class TextureLoader
{
public:
	static GLuint loadTexture( std::string texName, GLubyte* );
	static std::vector<Texture> loadedTextures;
};