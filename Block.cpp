#include "Block.h"
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define BLOCK_LENGTH 5
#define ROAD_WIDTH 15
#define COORD_DIST 50
#define COORD_DIST_HALF COORD_DIST / 2


Block::Block(int xCenter, int yCenter) : Drawable()
{

	locX = xCenter;
	locY = yCenter;

	for (int i = 0; i < BLOCK_LENGTH; i++) {
		for (int j = 0; j < BLOCK_LENGTH; j++) {

			coords[i][j] = std::make_pair(xCenter - 100 + 50 * i, yCenter - 100 + 50 * j);
		}
	}

	setCoordDisplacement();
	this->toWorld = this->toWorld * Matrix4().makeTranslate(locX, 0, locY);

}

Block::~Block() {}

void Block::draw(DrawData& data)
{

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(6.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < BLOCK_LENGTH; i++){
		for (int j = 0; j < BLOCK_LENGTH; j++) {
			glVertex3i(coords[i][j].first, 0, coords[i][j].second );
		}
	}
	glEnd();

	// draw road outline
	glBegin(GL_LINES);

	// vertical left
	for (int i = 0; i < BLOCK_LENGTH - 1; i++) {

		glVertex3i(coords[2][i].first - ROAD_WIDTH, 0, coords[2][i].second);
		glVertex3i(coords[2][i + 1].first - ROAD_WIDTH, 0, coords[2][i + 1].second);
	}
	
	// vertical right
	for (int i = 0; i < BLOCK_LENGTH - 1; i++) {

		glVertex3i(coords[2][i].first + ROAD_WIDTH, 0, coords[2][i].second);
		glVertex3i(coords[2][i + 1].first + ROAD_WIDTH, 0, coords[2][i + 1].second);
	}
	
	// horizontal bottom
	for (int i = 0; i < BLOCK_LENGTH - 1; i++) {

		glVertex3i(coords[i][2].first, 0, coords[i][2].second - ROAD_WIDTH);
		glVertex3i(coords[i + 1][2].first, 0, coords[i + 1][2].second - ROAD_WIDTH);
	}

	// horizontal top
	for (int i = 0; i < BLOCK_LENGTH - 1; i++) {

		glVertex3i(coords[i][2].first, 0, coords[i][2].second + ROAD_WIDTH);
		glVertex3i(coords[i + 1][2].first, 0, coords[i + 1][2].second + ROAD_WIDTH);
	}


	glEnd();


	glPopMatrix();
}


void Block::update(UpdateData& data)
{
	//
}


void Block::setCoordDisplacement() {

	srand(locX + locY);

	for (int i = 1; i < BLOCK_LENGTH - 1; i++) {
		for (int j = 1; j < BLOCK_LENGTH - 1; j++) {

			coords[i][j].first += rand() % COORD_DIST_HALF;
			coords[i][j].second += rand() % COORD_DIST_HALF;

		}
	}

}