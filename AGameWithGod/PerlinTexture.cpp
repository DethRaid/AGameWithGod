#include "PerlinTexture.h"

PerlinTexture::PerlinTexture() {
	pixels = new GLubyte[256*256*3];
	basePixels = new GLubyte[32*32];
	srand( time(NULL) );
	genTex();
}

PerlinTexture::PerlinTexture( int seed ) {
	pixels = new GLubyte[512*512*3];
	basePixels = new GLubyte[32*32];
	srand( seed );
	genTex();
}

PerlinTexture::~PerlinTexture() {
	delete[] pixels;
}

void PerlinTexture::genTex() {
	for( int i = 0; i < 32*32; i++ ) {
		basePixels[i] = rand();
	}
	GLuint *texture96 = new GLuint[96*96];
	GLuint *texture64 = new GLuint[64*64];
	GLuint *texture128 = new GLuint[128*128];
	GLuint *texture256 = new GLuint[256*256];

	for( int x = 0; x < 96; x++ ) {
		for( int y = 0; y < 96; y++ ) {
			texture96[x+y*96] = basePixels[(x%32) + (y%32)*32]; 
		}
	}

	for( int i = 0; i < 64*64; i++ ) {
		texture64[i] = getPixelBilinear( texture96, 
			32, 
			float(i%64)/float(64*3) + 0.333f, 
			float(i/64)/float(64*3) + 0.333f );
	}
	
	for( int i = 0; i < 128*128; i++ ) {
		texture128[i] = getPixelBilinear( texture96, 
			32, 
			float(i%128)/float(128*3) + 0.333f, 
			float(i/128)/float(128*3) + 0.333f );
	}
	
	for( int i = 0; i < 256*256; i++ ) {
		texture256[i] = getPixelBilinear( texture96, 
			32, 
			float(i%256)/float(256*3) + 0.333f, 
			float(i/256)/float(256*3) + 0.333f );
	}

	GLuint value, biggest = 0;

	for( int x = 0; x < 256; x++ ) {
		for( int y = 0; y < 256; y++ ) {
			value = texture256[(x%256) + (y%256)*256]/2 + (texture128[(x%128) + 
				(y%128)*128]/4) + (texture64[(x%64) + (y%64)*64]/8)  + (basePixels[(x%32) + (y%32)*32]/16);
			if( value > biggest )
				biggest = value;
			texture256[x + y*256] = value;
		}
	}

	//normalize the texture
	for( int i = 0; i < 256*256; i++ ) {
		texture256[i] = double(texture256[i])/double(biggest) * 256;
	}

	for( int i = 0; i < 256*256; i++ ) {
		pixels[i] = texture256[i];
	}

	//after generating the texture, we'll give it a simple blur just to get rid of the horrendous lines I refuse to correct
}

void PerlinTexture::makeGLTex() {
	//Throw the texture into the graphics card
	glGenTextures( 1, &glID );

	glBindTexture( GL_TEXTURE_2D, glID );
	if( glIsTexture( glID ) ) {
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR  );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR  );
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );

		GLfloat fLargest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);

		gluBuild2DMipmaps( GL_TEXTURE_2D, GL_LUMINANCE, 256, 256, GL_LUMINANCE, GL_UNSIGNED_BYTE, pixels );
	}
}

//assumes a square texture
//pixels is the array of pixels we want to deal with
//side is the size of a side of pixels
//u and v are the coordinates of the pixel we want
GLuint PerlinTexture::getPixelBilinear( GLuint *pixels, int side, float u, float v ) {
	u = u * side - 0.5;
	v = v * side - 0.5;
	int x = floor( u );
	int y = floor( v );
	float uRatio = u - x;
	float vRatio = v - y;
	float uOpposite = 1 - uRatio;
	float vOpposite = 1 - vRatio;
	return (pixels[x + y*32] * uOpposite + pixels[x+1 + y*32] * uRatio) * vOpposite +
		(pixels[x + (y+1)*32] * uOpposite + pixels[x+1 + (y+1)*32] * uRatio) * vRatio;
}

/*
Grabs a bilinearly filtered pixel from the final image.
*/
GLuint PerlinTexture::getPixelBilinear( float u, float v ) {
	u = u*256 - 0.5;
	v = v*256 - 0.5;
	int x = floor( u );
	int y = floor( v );
	float uRatio = u - x;
	float vRatio = v - y;
	float uOpposite = 1 - uRatio;
	float vOpposite = 1 - vRatio;
	return (pixels[x + y*32] * uOpposite + pixels[x+1 + y*32] * uRatio) * vOpposite +
		(pixels[x + (y+1)*32] * uOpposite + pixels[x+1 + (y+1)*32] * uRatio) * vRatio;
}