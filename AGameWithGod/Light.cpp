#include "Light.h"

Light::Light(void)
{
	for( int i = 0; i < 4; i++ )
	{
		ambient[i] = 0.2f;
		diffuse[i] = 1.0f;
		specular[i] = 1.0f;
		position[i] = 0.0f;
	}
}

Light::Light( int d )
{
	dataValue = d;
	for( int i = 0; i < 4; i++ )
	{
		ambient[i] = 0.0f;
		diffuse[i] = 1.0f;
		specular[i] = 1.0f;
		if( i < 3 ) {
			position[i] = 0.0f;
		}
	}
}

void Light::enable()
{	
	float *f = new float[3];
	glLightfv( dataValue, GL_AMBIENT, ambient );
	glLightfv( dataValue, GL_DIFFUSE, diffuse );
	glLightfv( dataValue, GL_SPECULAR, specular );
	glLightfv( dataValue, GL_POSITION, position.toArray( f ) );
	glEnable( dataValue );
	delete[] f;
}

void Light::disable()
{
	glDisable( dataValue );
}

void Light::updatePosition()
{	
	float *f = new float[3];
	glLightfv( dataValue, GL_POSITION, position.toArray( f ) );
	delete[] f;
}

void Light::setAmbientColor( GLfloat r, GLfloat g, GLfloat b, GLfloat a )
{
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;
}

void Light::setDiffuseColor( GLfloat r, GLfloat g, GLfloat b, GLfloat a )
{
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
}

void Light::setSpecularColor( GLfloat r, GLfloat g, GLfloat b, GLfloat a )
{
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;
}

void Light::setPosition( GLfloat x, GLfloat y, GLfloat z )
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

void Light::setDirection( GLfloat x, GLfloat y, GLfloat z )
{
	direction[0] = x;
	direction[1] = y;
	direction[2] = z;
	direction.normalize();
}

Light::~Light(void)
{}