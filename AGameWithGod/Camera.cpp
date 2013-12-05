#include "Camera.h"

Camera::Camera()
{
	transform.moveTo( Vector3( 0, 0, -10 ) );
	transform.setRotation( Vector3( 0, 180, 0 ) );
	aspectRatio = 1.0f;
	fieldOfView = 60;
	nearClipPlane = 0.1f;
	farClipPlane = 100.0f;
}

Camera::~Camera()
{}

std::string Camera::toString()
{
	std::ostringstream value;
	value<<"Position: (" <<transform.getXPos() <<", " <<transform.getYPos() <<", " <<transform.getZPos() <<")\n";
	value<<"Rotation: (" <<transform.getXRot() <<", " <<transform.getYRot() <<", " <<transform.getZRot() <<")\n";
	value<<"Aspect ratio: " <<aspectRatio <<"\n";
	value<<"Field of view: " <<fieldOfView <<"\n";
	value<<"Near clipping plane: " <<nearClipPlane <<"\n";
	value<<"Far clipping plane: " <<farClipPlane <<"\n";
	return value.str();
}