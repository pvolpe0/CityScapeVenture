#include "Camera.h"

Camera::Camera()
{
    c.identity();
    e.set(0.0, 5.0, 20.0);
    d.set(0.0, 9.0, 0.0);
    up.set(0.0, 1.0, 0.5);
    
    //Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
    //This is used as a default camera position for Project 1
    c.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, e[0], e[1], e[2], 1);
    ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);
	update();
	c.print("normal");
	ci.print("inverse");
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
		e[0], e[1], e[2], 1);
	ci = c.rigidInverse();

}

void Camera::set(Vector3& e, Vector3& d, Vector3& up)
{
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}

void Camera::transform(Matrix4& transformation)
{
	c = c * transformation;
	ci = c.rigidInverse();
}
