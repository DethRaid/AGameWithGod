#include "Temple.h"

Temple::Temple() : Actor() {
	mesh.readOBJ( "Temple.obj" );
}

Temple::~Temple() {}

void Temple::init() {
	texture = TextureLoader::loadTexture( "Temple.png", NULL );
}

void Temple::render() {
	float *lightDir = new float[4];
	lightDir[0] = lightDir[1] = 1;
	lightDir[2] = .3;
	lightDir[3] = 0;
	glPushMatrix();
	glTranslatef( 0, 0, 400 );
	glRotatef( 180, 0, 1, 0 );
	Shaders::getDiffuse().bind();
	glLightfv( GL_LIGHT0, GL_POSITION, lightDir );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, texture );
	mesh.render();
	glPopMatrix();
}