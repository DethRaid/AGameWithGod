#pragma once

#include "stdafx.h"

#include "Vector3.h"

class Transform
{
	public:
		Transform(void) : position( 0, 0, 0 ), rotation( 0, 0, 0 ) {updateVectors();};
		Transform( HWND &hwnd ) : position( 0, 0, 0 ), rotation( 0, 0, 0 ) {hWnd = hwnd; updateVectors();};
		Transform( Vector3 pos, Vector3 rot ) : position( pos ), rotation( rot ) {};
		~Transform(void);

		void translate( Vector3 );
		void moveTo( Vector3 pos ) {position = pos;};
		void rotate( Vector3 );
		void setRotation( Vector3 );
		void updateVectors();

		Vector3 getPosition() {return position;};
		float getXPos() {return position.getX();};
		float getYPos() {return position.getY();};
		float getZPos() {return position.getZ();};

		Vector3 getRotation() {return rotation;};
		float getXRot() {return rotation.getX();};
		float getYRot() {return rotation.getY();};
		float getZRot() {return rotation.getZ();};
		
		Vector3 getForward() {return forward;};
		Vector3 getRight() {return right;};
		Vector3 getUp() {return up;};

	private:
		Vector3 position;
		Vector3 rotation;
		Vector3 forward, right, up;
		HWND hWnd;
		float sx, sy, sz, cx, cy, cz, theta;
		Vector3 angles;
};

