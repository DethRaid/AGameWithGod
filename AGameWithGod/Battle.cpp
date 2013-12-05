#include "Battle.h"

Battle::Battle() {
	fighters = new BattleActor[10];
}

Battle::~Battle() {
	delete[] fighters;
}

void Battle::init() {
	for( int i = 0; i < 10; i++ ) {
		fighters[i].init();
	}
}

void Battle::update() {
	for( int i = 0; i < 10; i++ ) {
		fighters[i].update( fighters );
	}
}

void Battle::render() {
	glPushMatrix();
	glTranslatef( center.getX(), center.getY(), center.getZ() );
	for( int i = 0; i < 10; i++ ) {
		fighters[i].render();
	}
	glPopMatrix();
}