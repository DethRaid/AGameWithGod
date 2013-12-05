#ifndef CAMERA_H
#define CAMERA_H

#include "stdafx.h"

#include "Vector3.h"
#include "Transform.h"

class Camera
{
	public:
		Camera(void);
		//Camera( std::ofstream );
		Camera( HWND &hWnd ) : transform( hWnd ) {};
		~Camera(void);

		void translate( Vector3 distance ) {transform.moveTo( Vector3(transform.getXPos()+distance.getX(), 
																	  transform.getYPos()+distance.getY(),
																	  transform.getZPos()+distance.getZ()) );};

		void rotate( Vector3 theta ) {transform.setRotation( Vector3(transform.getXRot()+theta.getX(),
																	 transform.getYRot()+theta.getY(),
																	 transform.getZRot()+theta.getZ()) );};

		void setPosition( float x, float y, float z ) {transform.moveTo( Vector3(x, y, z) );};
		void setRotation( float x, float y, float z ) {transform.setRotation( Vector3(x, y, z) );};

		void setAspectRatio( float f ) {aspectRatio = f;};
		void setNearClipPlane( float f ) {nearClipPlane = f;};
		void setFarClipPlane( float f ) {farClipPlane = f;};
		void setFieldOfView( int i ) {(i < 180 ? (i > 0 ? fieldOfView = i : fieldOfView = 0) : fieldOfView = 180);};

		float getAspectRatio() {return aspectRatio;};
		float getNearClipPlane() {return nearClipPlane;};
		float getFarClipPlane() {return farClipPlane;};
		int getFieldOfView() {return fieldOfView;};

		Vector3 getPosition() {return transform.getPosition();};
		float getXPos() {return transform.getXPos();};
		float getYPos() {return transform.getYPos();};
		float getZPos() {return transform.getZPos();};

		Vector3 getRotation() {return transform.getRotation();};
		float getXRot() {return transform.getXRot();};
		float getYRot() {return transform.getYRot();};
		float getZRot() {return transform.getZRot();};

		Transform& getTransform() {return transform;};

		std::string toString();

	private:
		float aspectRatio, nearClipPlane, farClipPlane;
		int fieldOfView; 
		Transform transform;
};

#endif