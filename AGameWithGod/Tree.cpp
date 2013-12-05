#include "Tree.h"

Tree::Tree() : Actor() {
	canDraw = false;
}

Tree::Tree( Vector3 pos ) : Actor( pos ) {
	canDraw = false;
}

Tree::~Tree() {}

void Tree::init() {
	texture = TextureLoader::loadTexture( "Tree.png", NULL );
}

void Tree::render() {	
	if( canDraw ) {
		glPushMatrix();
		glTranslatef( transform.getPosition().getX(), 
			transform.getPosition().getY(), 
			transform.getPosition().getZ() );
			glTexCoord2d( 0, 0 );
			glVertex3f( -1, 4, 0 );
			glTexCoord2d( 1, 0 );
			glVertex3f( 1, 4, 0 );
			glTexCoord2d( 1, 1 );
			glVertex3f( 1, 0, 0 );
			glTexCoord2d( 0, 1 );
			glVertex3f( -1, 0, 0);

		glRotated( 90, 0, 1, 0 );
	
			glTexCoord2d( 0, 0 );
			glVertex3f( -1, 4, 0 );
			glTexCoord2d( 1, 0 );
			glVertex3f( 1, 4, 0 );
			glTexCoord2d( 1, 1 );
			glVertex3f( 1, 0, 0 );
			glTexCoord2d( 0, 1 );
			glVertex3f( -1, 0, 0 );
		glPopMatrix();
	}
}