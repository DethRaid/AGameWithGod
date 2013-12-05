#pragma once
#include "stdafx.h"
#include "TextureLoader.h"

class SplashScreen
{
public:
	SplashScreen(void);
	~SplashScreen(void);

	void init();

	void render( double time );
private:
	GLuint presents;
	GLuint title;
};

