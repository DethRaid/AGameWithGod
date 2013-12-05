#include "Player.h"

Player::Player(void) {
	transform.translate( Vector3(0, 1.5, 0 ) );
}

Player::~Player(void)
{}

void Player::loadView() {
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glRotated( transform.getXRot(), 1, 0, 0 );
	glRotated( transform.getYRot(), 0, 1, 0 );
	glRotated( transform.getZRot(), 0, 0, 1 );
	glTranslated( -transform.getXPos(), -transform.getYPos(), -transform.getZPos() );
	glRotated( camera.getXRot(), 1, 0, 0 );
	glRotated( camera.getYRot(), 0, 1, 0 );
	glRotated( camera.getZRot(), 0, 0, 1 );
	glTranslated( -camera.getXPos(), -camera.getYPos(), -camera.getZPos() );
}

void Player::fire() {
	firstShot = true;
	shooting = true;
}

void Player::update() {
	if( firstShot ) {
		firstShot = false;
		projectilePos = transform.getPosition();
		projectileStart = projectilePos;
		projectileDir = transform.getForward();
	}
	if( shooting ) {
		projectilePos += projectileDir * 5;
		if( Vector3::distance( projectilePos, projectileStart ) > 50 ) {
			shooting = false;
		}
	}
}

void Player::render() {
	if( shooting ) {
		Shaders::getEmit().bind();
		Shaders::getEmit().setVariable( "color", 1.0, 0.0, 0.0, 1.0 );
		glPushMatrix();
		glTranslated( projectilePos.getX(), projectilePos.getY(), projectilePos.getZ() );
		glBegin( GL_QUADS );
		glVertex3f( -.5, -.5, 0 );
		glVertex3f( -.5, .5, 0 );
		glVertex3f( .5, .5, 0 );
		glVertex3f( .5, -.5, 0 );
		glEnd();
		glPopMatrix();
	}
}