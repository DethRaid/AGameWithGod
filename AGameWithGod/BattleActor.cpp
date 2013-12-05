#include "BattleActor.h"

BattleActor::BattleActor(void) {
	speed = 1;
}

BattleActor::~BattleActor(void) {}

void BattleActor::init() {
	if( rand() < RAND_MAX/2 ) {
		blendFac = 1;
	} else {
		blendFac = 0;
	}
	FILE *file = fopen( "Human.png", "rb" );
	int x, y, comp;
	humanTex.pixels = stbi_load_from_file( file, &x, &y, &comp, 0 );
	humanTex.x = x;
	humanTex.y = y;
	fclose( file );
	file = fopen( "Monster.png", "rb" );
	humanTex.pixels = stbi_load_from_file( file, &x, &y, &comp, 0 );
	humanTex.x = x;
	humanTex.y = y;
	fclose( file );
	glEnable( GL_TEXTURE_2D );

	glGenTextures( 1, &(tex.glName) );

	glBindTexture( GL_TEXTURE_2D, tex.glName );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR  );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR  );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
	
	GLfloat fLargest;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
	buildTexture();
}

void BattleActor::buildTexture() {
	for( int i = 0; i < humanTex.x*humanTex.y*4; i++ ) {
		tex.pixels[i] = humanTex.pixels[i] * blendFac + monsterTex.pixels[i] * (1-blendFac);
	}
	glBindTexture( GL_TEXTURE_2D, tex.glName );
	gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, tex.x, tex.y, GL_RGBA, GL_UNSIGNED_BYTE, tex.pixels );
}

void BattleActor::render() {
	glPushMatrix();
	glTranslatef( transform.getPosition().getX(), transform.getPosition().getY(), transform.getPosition().getZ() );
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	Shaders::getDiffuse().bind();
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, texture );
	glBegin( GL_QUADS );
		glTexCoord2d( 0, 1 );
		glVertex3f( -1, 4, 0 );
		glTexCoord2d( 1, 1 );
		glVertex3f( 1, 4, 0 );
		glTexCoord2d( 1, 0 );
		glVertex3f( 1, 0, 0 );
		glTexCoord2d( 0, 0 );
		glVertex3f( -1, 0, 0);
	glEnd();
	glPopMatrix();
}

void BattleActor::update( BattleActor *others ) {
	if( blendFac > 0.01 ) {
		blendFac = 1 - Globals::battleFactor;
	}
	curFrame++;
	if( curFrame%100 == 0 ) {
		buildTexture();
	}
	float closestDist = 10000, curDist = 0;
	int closestInd = 0, curInd = 0;
	for( int i = 0; i < 10; i++ ) {
		curInd++;
		if( &others[i] != this ) {
			curDist = Vector3::distance( others[i].getTransform().getPosition(), transform.getPosition() );
			if( curDist < closestDist ) {
				closestDist = curDist;
				closestInd = curInd;
			}
		}
	}
	target = &(others[closestInd]);
	Vector3 dir = target->getTransform().getPosition() - transform.getPosition();
	dir.normalize();
	transform.translate( dir * speed );
}