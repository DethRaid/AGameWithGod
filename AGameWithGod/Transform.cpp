#include "Transform.h"

Transform::~Transform()
{}

void Transform::translate( Vector3 distance )
{
	position += distance;
}

void Transform::rotate( Vector3 rot )
{
	rotation += rot;
	updateVectors();
}

void Transform::setRotation( Vector3 rot )
{
	rotation.set( rot.getX(), rot.getY(), rot.getZ() );
	updateVectors();
}

void Transform::updateVectors()
{	
	angles.set( rotation.getY(), rotation.getZ(), rotation.getX() );

    // rotation angle about X-axis (pitch)
    theta = angles[0] * DEG2RAD;
    sx = sinf(theta);
    cx = cosf(theta);

    // rotation angle about Y-axis (yaw)
    theta = angles[1] * DEG2RAD;
    sy = sinf(theta);
    cy = cosf(theta);

    // rotation angle about Z-axis (roll)
    theta = angles[2] * DEG2RAD;
    sz = sinf(theta);
    cz = cosf(theta);

    // determine right vector
    right.setX( cy*cz - sy*sx*sz );
    right.setY( cy*sz + sy*sx*cz );
    right.setZ( -sy*cx );

    // determine up vector
    up.setX( -cx*sz );
    up.setY( cx*cz );
    up.setZ( sx );

    // determine forward vector
    forward.setY( sy*cz + cy*sx*sz );
    forward.setX( sy*sz - cy*sx*cz );
    forward.setZ( cy*cx );
}