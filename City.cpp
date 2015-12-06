#include "City.h"
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define CITY_LENGTH 5

City::City() : Drawable()
{
	
	for (int i = 0; i < CITY_LENGTH; i++) {
		for (int j = 0; j < CITY_LENGTH; j++) {

			blocks[i][j] = new Block(-200 + 100 * i, -200 + 100 * j);
		}
	}
}

City::~City() {}

void City::draw(DrawData& data)
{

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	
	for (int i = 0; i < CITY_LENGTH; i++) {
		for (int j = 0; j < CITY_LENGTH; j++) {

			blocks[i][j]->draw(data);
		}
	}


	glPopMatrix();
}


void City::update(UpdateData& data)
{
	//
}


