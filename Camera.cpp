#include "Camera.h"

Camera::Camera()
{
    c.identity();
    e.set(0.0, 10.0, 0.0);
    d.set(0.0, 10.0, 1.0);
    up.set(0.0, 1.0, 0.0);
    
    //Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
    //This is used as a default camera position for Project 1
    c.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, e[0], e[1], e[2], 1);
    ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);
	update();
}

Camera::~Camera()
{
    //Delete and dynamically allocated memory/objects here
}

Matrix4& Camera::getMatrix()
{
    return c;
}

Matrix4& Camera::getInverseMatrix()
{
    return ci;
}

void Camera::update()
{
	Vector3 zc = (e - d) * (1 / ((e - d).magnitude()));
	Vector3 xc = (up.cross(zc)) * (1 / (up.cross(zc)).magnitude());
	Vector3 yc = zc.cross(xc);
	c.set(xc[0], xc[1], xc[2], 0,
		  yc[0], yc[1], yc[2], 0,
		  zc[0], zc[1], zc[2], 0,
		   e[0],  e[1],  e[2], 1);
	ci = c.rigidInverse();

}

void Camera::set(Vector3& e, Vector3& d, Vector3& up)
{
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}

// Transforms camera matrix based on passed in matrix
void Camera::transform(Matrix4 transformation)
{
	c = c * transformation;
	ci = c.rigidInverse();
}

// Rotates camera about camera position
void Camera::rotate(Matrix4& rotation)
{
	d = (rotation * (d - e)) + e;
	update();
}

// Moves camera based on movement vector
void Camera::move(Vector3& movement)
{
	this->e = this->e + movement;
	this->d = this->d + movement;
	update();
}

void Camera::look(float dir)
{
	if (d[1] + dir > 40)
		d[1] = 40;
	else if (d[1] + dir < -40)
		d[1] = -40;
	else
		d[1] += dir;
}

Vector3 Camera::getDirection(void)
{
	return (Vector3(e[0] - d[0], 0, e[2] - d[2])).normalize();
}