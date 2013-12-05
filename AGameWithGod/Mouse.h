#pragma once

#define LEFT_MOUSE_BUTTON 0
#define RIGHT_MOUSE_BUTTON 1
#define MIDDLE_MOUSE_BUTTON 2

class Mouse
{
public:
	static bool button0;
	static bool button1;
	static bool button2;
	static int x;
	static int y;
	static int lastX;
	static int lastY;
	static int nextX;
	static int nextY;

	static float delta();
};

