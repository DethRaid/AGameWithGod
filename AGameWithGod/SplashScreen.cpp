#include "SplashScreen.h"

SplashScreen::SplashScreen(void) {}

SplashScreen::~SplashScreen(void)
{}

void SplashScreen::init() {	
	presents = TextureLoader::loadTexture( "Presents.png", NULL );
	title = TextureLoader::loadTexture( "Title.png", NULL );
}

void SplashScreen::render( double time ) {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	if( time < 3 ) {
		glBindTexture( GL_TEXTURE_2D, presents );
	} else {
		glBindTexture( GL_TEXTURE_2D, title );
	}
	glColor3f( 1.0f, 1.0f, 1.0f );
	glBegin( GL_QUADS );
		glTexCoord2f( 0.0, 1.0 );
		glVertex3f( -1.0, -1.0, -1.5 );
		glTexCoord2f( 1.0, 1.0 );
		glVertex3f( 1.0, -1.0, -1.5 );
		glTexCoord2f( 1.0, 0.0 );
		glVertex3f( 1.0, 1.0, -1.5 );
		glTexCoord2f( 0.0, 0.0 ); 
		glVertex3f( -1.0, 1.0, -1.5 );
	glEnd();
}