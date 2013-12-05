#pragma once

#include "stdafx.h"
#include "Vector3.h"

class Light
{
	public:
		Light(void);
		Light( int );
		~Light(void);

		virtual void enable();
		virtual void disable();

		void setAmbientColor( GLfloat, GLfloat, GLfloat, GLfloat );
		void setDiffuseColor( GLfloat, GLfloat, GLfloat, GLfloat );
		void setSpecularColor( GLfloat, GLfloat, GLfloat, GLfloat );
		void setPosition( GLfloat, GLfloat, GLfloat );
		void setDirection( GLfloat, GLfloat, GLfloat );

		void updatePosition();

		GLfloat* getAmbient() {return ambient;};
		GLfloat* getDiffuse() {return diffuse;};
		GLfloat* getSpecular() {return specular;};
		Vector3& getPosition() {return position;};
		Vector3& getDirection() {return direction;};

	protected:
		int dataValue;
		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
		Vector3 position;
		Vector3 direction;
};

