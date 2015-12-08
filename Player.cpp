#include "Player.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include "Matrix4.h"

Player::Player() : Drawable()
{
	x = y = 0;
	sphere = new Sphere(5, 20, 20);
}

Player::~Player()
{
	delete sphere;
}


void Player::draw(DrawData& data)
{


	//Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
	glMatrixMode(GL_MODELVIEW);

	//Push a save state onto the matrix stack, and multiply in the toWorld matrix
	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	sphere->draw(data);

	//The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
	//glutSolidCube(size);

	//Pop the save state off the matrix stack
	//This will undo the multiply we did earlier
	glPopMatrix();
}

void Player::setDeltaLocation(int deltaX, int deltaY) {

	x += deltaX;
	y += deltaY;
}

void Player::update(UpdateData& data)
{
	//
}

Vector4 Player::getLocation(void)
{
	return Vector4(x, 0, y, 1);
}

