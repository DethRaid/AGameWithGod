#include "Actor.h"

Actor::Actor()
{}

Actor::~Actor(void)
{}

int Actor::loadImage( std::string filename, GLubyte* data ) {
	return TextureLoader::loadTexture( filename, data );
}

void Actor::setHeight( float height ) {
	transform.moveTo( Vector3( transform.getXPos(), height, transform.getZPos() ) );
};