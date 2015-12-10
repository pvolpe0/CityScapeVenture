#include "Player.h"
#include "Globals.h"

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
	atIntersection = 1;
	currInt = Vector3(Globals::city.blocks[2][2]->getBotLeftCoord().first, 0, Globals::city.blocks[2][2]->getBotLeftCoord().second);
	southInt = Vector3(Globals::city.blocks[2][1]->getBotLeftCoord().first, 0, Globals::city.blocks[2][1]->getBotLeftCoord().second);
	northInt = Vector3(Globals::city.blocks[2][3]->getBotLeftCoord().first, 0, Globals::city.blocks[2][3]->getBotLeftCoord().second);
	westInt = Vector3(Globals::city.blocks[1][2]->getBotLeftCoord().first, 0, Globals::city.blocks[1][2]->getBotLeftCoord().second);
	eastInt = Vector3(Globals::city.blocks[3][2]->getBotLeftCoord().first, 0, Globals::city.blocks[3][2]->getBotLeftCoord().second);
	northMove = (northInt - currInt).scale(0.2);
	southMove = (southInt - currInt).scale(0.2);
	westMove = (westInt - currInt).scale(0.2);
	eastMove = (eastInt - currInt).scale(0.2);
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


	//The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
	//glutSolidCube(size);

	//Pop the save state off the matrix stack
	//This will undo the multiply we did earlier
	glPopMatrix();
}

void Player::setDeltaLocation(float deltaX, float deltaY) {

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

void Player::moveNorth()
{
	setDeltaLocation(northMove[0], northMove[2]);
	Globals::camera.move(Vector3(northMove[0], 0, northMove[2]));
	Globals::skybox->toWorld = Globals::skybox->toWorld * Matrix4().makeTranslate(northMove[0], 0, northMove[2]);
	if (atIntersection)
	{
		southInt = currInt;
		southMove = (southInt - northInt).scale(0.2);
		eastMove = Vector3(0, 0, 0);
		westMove = Vector3(0, 0, 0);
		atIntersection = 0;
	}
	else if (abs(int(x) - northInt[0]) < 2 && abs(int(y) - northInt[2]) < 2)
	{
		x = northInt[0];
		y = northInt[2];
		currInt = northInt;
		if (currInt[0] != Globals::city.blocks[2][2]->getBotLeftCoord().first
			|| currInt[2] != Globals::city.blocks[2][2]->getBotLeftCoord().second)
		{
			std::cout << "Intersection hit" << std::endl;
			Globals::city.generateRowWest();
		}
		currInt = Vector3(Globals::city.blocks[2][2]->getBotLeftCoord().first, 0, Globals::city.blocks[2][2]->getBotLeftCoord().second);
		southInt = Vector3(Globals::city.blocks[2][1]->getBotLeftCoord().first, 0, Globals::city.blocks[2][1]->getBotLeftCoord().second);
		northInt = Vector3(Globals::city.blocks[2][3]->getBotLeftCoord().first, 0, Globals::city.blocks[2][3]->getBotLeftCoord().second);
		westInt = Vector3(Globals::city.blocks[1][2]->getBotLeftCoord().first, 0, Globals::city.blocks[1][2]->getBotLeftCoord().second);
		eastInt = Vector3(Globals::city.blocks[3][2]->getBotLeftCoord().first, 0, Globals::city.blocks[3][2]->getBotLeftCoord().second);
		northMove = (northInt - currInt).scale(0.2);
		southMove = (southInt - currInt).scale(0.2);
		westMove = (westInt - currInt).scale(0.2);
		eastMove = (eastInt - currInt).scale(0.2);;
		atIntersection = 1;

	}
}

void Player::moveSouth()
{
	setDeltaLocation(southMove[0], southMove[2]);
	Globals::camera.move(Vector3(southMove[0], 0, southMove[2]));
	Globals::skybox->toWorld = Globals::skybox->toWorld * Matrix4().makeTranslate(southMove[0], 0, southMove[2]);
	if (atIntersection)
	{
		northInt = currInt;
		northMove = (northInt - southInt).scale(0.2);
		eastMove = Vector3(0, 0, 0);
		westMove = Vector3(0, 0, 0);
		atIntersection = 0;
	}
	else if (abs(int(x) - southInt[0]) < 2 && abs(int(y) - southInt[2]) < 2)
	{
		x = southInt[0];
		y = southInt[2];
		currInt = southInt;
		if (currInt[0] != Globals::city.blocks[2][2]->getBotLeftCoord().first
			|| currInt[2] != Globals::city.blocks[2][2]->getBotLeftCoord().second)
		{
			std::cout << "Intersection hit" << std::endl;
			Globals::city.generateRowEast();
		}
		currInt = Vector3(Globals::city.blocks[2][2]->getBotLeftCoord().first, 0, Globals::city.blocks[2][2]->getBotLeftCoord().second);
		southInt = Vector3(Globals::city.blocks[2][1]->getBotLeftCoord().first, 0, Globals::city.blocks[2][1]->getBotLeftCoord().second);
		northInt = Vector3(Globals::city.blocks[2][3]->getBotLeftCoord().first, 0, Globals::city.blocks[2][3]->getBotLeftCoord().second);
		westInt = Vector3(Globals::city.blocks[1][2]->getBotLeftCoord().first, 0, Globals::city.blocks[1][2]->getBotLeftCoord().second);
		eastInt = Vector3(Globals::city.blocks[3][2]->getBotLeftCoord().first, 0, Globals::city.blocks[3][2]->getBotLeftCoord().second);
		northMove = (northInt - currInt).scale(0.2);
		southMove = (southInt - currInt).scale(0.2);
		westMove = (westInt - currInt).scale(0.2);
		eastMove = (eastInt - currInt).scale(0.2);;
		atIntersection = 1;

	}
}


void Player::moveWest()
{
	setDeltaLocation(westMove[0], westMove[2]);
	Globals::camera.move(Vector3(westMove[0], 0, westMove[2]));
	Globals::skybox->toWorld = Globals::skybox->toWorld * Matrix4().makeTranslate(westMove[0], 0, westMove[2]);
	if (atIntersection)
	{
		eastInt = currInt;
		eastMove = (eastInt - westInt).scale(0.2);
		southMove = Vector3(0, 0, 0);
		northMove = Vector3(0, 0, 0);
		atIntersection = 0;
	}
	else if (abs(int(x) - westInt[0]) < 2 && abs(int(y) - westInt[2]) < 2)
	{
		x = westInt[0];
		y = westInt[2];
		currInt = westInt;
		if (currInt[0] != Globals::city.blocks[2][2]->getBotLeftCoord().first
			|| currInt[2] != Globals::city.blocks[2][2]->getBotLeftCoord().second)
		{
			std::cout << "Intersection hit" << std::endl;
			Globals::city.generateRowSouth();
		}
		currInt = Vector3(Globals::city.blocks[2][2]->getBotLeftCoord().first, 0, Globals::city.blocks[2][2]->getBotLeftCoord().second);
		southInt = Vector3(Globals::city.blocks[2][1]->getBotLeftCoord().first, 0, Globals::city.blocks[2][1]->getBotLeftCoord().second);
		northInt = Vector3(Globals::city.blocks[2][3]->getBotLeftCoord().first, 0, Globals::city.blocks[2][3]->getBotLeftCoord().second);
		westInt = Vector3(Globals::city.blocks[1][2]->getBotLeftCoord().first, 0, Globals::city.blocks[1][2]->getBotLeftCoord().second);
		eastInt = Vector3(Globals::city.blocks[3][2]->getBotLeftCoord().first, 0, Globals::city.blocks[3][2]->getBotLeftCoord().second);
		northMove = (northInt - currInt).scale(0.2);
		southMove = (southInt - currInt).scale(0.2);
		westMove = (westInt - currInt).scale(0.2);
		eastMove = (eastInt - currInt).scale(0.2);;
		atIntersection = 1;

	}
}

void Player::moveEast()
{
	setDeltaLocation(eastMove[0], eastMove[2]);
	Globals::camera.move(Vector3(eastMove[0], 0, eastMove[2]));
	Globals::skybox->toWorld = Globals::skybox->toWorld * Matrix4().makeTranslate(eastMove[0], 0, eastMove[2]);
	if (atIntersection)
	{
		westInt = currInt;
		westMove = (westInt - eastInt).scale(0.2);
		southMove = Vector3(0, 0, 0);
		northMove = Vector3(0, 0, 0);
		atIntersection = 0;
	}
	else if (abs(int(x) - eastInt[0]) < 2 && abs(int(y) - eastInt[2]) < 2)
	{
		x = eastInt[0];
		y = eastInt[2];
		currInt = eastInt;
		if (currInt[0] != Globals::city.blocks[2][2]->getBotLeftCoord().first
			|| currInt[2] != Globals::city.blocks[2][2]->getBotLeftCoord().second)
		{
			std::cout << "Intersection hit" << std::endl;
			Globals::city.generateRowNorth();
		}
		currInt = Vector3(Globals::city.blocks[2][2]->getBotLeftCoord().first, 0, Globals::city.blocks[2][2]->getBotLeftCoord().second);
		southInt = Vector3(Globals::city.blocks[2][1]->getBotLeftCoord().first, 0, Globals::city.blocks[2][1]->getBotLeftCoord().second);
		northInt = Vector3(Globals::city.blocks[2][3]->getBotLeftCoord().first, 0, Globals::city.blocks[2][3]->getBotLeftCoord().second);
		westInt = Vector3(Globals::city.blocks[1][2]->getBotLeftCoord().first, 0, Globals::city.blocks[1][2]->getBotLeftCoord().second);
		eastInt = Vector3(Globals::city.blocks[3][2]->getBotLeftCoord().first, 0, Globals::city.blocks[3][2]->getBotLeftCoord().second);
		northMove = (northInt - currInt).scale(0.2);
		southMove = (southInt - currInt).scale(0.2);
		westMove = (westInt - currInt).scale(0.2);
		eastMove = (eastInt - currInt).scale(0.2);;
		atIntersection = 1;

	}
}


