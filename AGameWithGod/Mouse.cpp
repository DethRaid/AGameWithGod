#include "stdafx.h"
#include "Mouse.h"

int Mouse::x = 0;
int Mouse::y = 0;
int Mouse::lastX = 0;
int Mouse::lastY = 0;
int Mouse::nextX = 0;
int Mouse::nextY = 0;
bool Mouse::button0 = false;
bool Mouse::button1 = false;
bool Mouse::button2 = false;

float Mouse::delta() {
	return sqrtf( float((x-lastX)*(x-lastX)) + float((y-lastY)*(y-lastY)) );
}