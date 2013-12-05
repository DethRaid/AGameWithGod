#pragma once

#include "stdafx.h"
#include "Transform.h"
#include "TextureLoader.h"

class Actor
{
public:
	Actor();
	Actor( Vector3 pos ) : transform( pos, Vector3::zero ) {};
	~Actor();
	int loadImage( std::string, GLubyte* );
	void setHeight( float );
	Transform& getTransform() {return transform;};
	virtual void render() = 0;
protected:
	Transform transform;
};

