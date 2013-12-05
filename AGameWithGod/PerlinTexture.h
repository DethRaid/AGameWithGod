#pragma once
#include "stdafx.h"

#define setup(i,b0,b1,r0,r1)\
	t = vec[i] + N;\
	b0 = ((int)t) & BM;\
	b1 = (b0+1) & BM;\
	r0 = t - (int)t;\
	r1 = r0 - 1.;

class PerlinTexture
{
public:
	PerlinTexture();
	PerlinTexture( int );
	~PerlinTexture();

	void init();
	void makeGLTex();
	GLubyte getPixel( int i ) {return pixels[i];};
	GLuint getPixelBilinear( GLuint*, int, float, float );
	GLuint getPixelBilinear( float, float );
	GLubyte* getPixels() {return pixels;};
	GLuint getGLID() {return glID;};

	int sCurve( int t ) {return t * t * (3. - 2. * t);};	//3t^2 + 2t^3
	int lerp( int t, int a, int b ) {return a + t * (b - a);};
	float lerp( float t, float a, float b ) {return a + t * (b - a);};

private:
	GLubyte *pixels;
	GLubyte *basePixels;
	GLuint glID;

	void genTex();
};

