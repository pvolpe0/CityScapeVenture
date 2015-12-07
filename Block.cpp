#include "Block.h"
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define BLOCK_LENGTH 2
#define ROAD_WIDTH 15
#define COORD_DIST 200
#define COORD_DIST_HALF COORD_DIST / 1
#define COORD_DIST_QUARTER COORD_DIST / 2

// line color
#define LINE_RED 242
#define LINE_GREEN 223
#define LINE_BLUE 94


Block::Block(int xCenter, int yCenter) : Drawable()
{

	locX = xCenter;
	locY = yCenter;
	srand(locX + locY);

	for (int i = 0; i < BLOCK_LENGTH; i++) {
		for (int j = 0; j < BLOCK_LENGTH; j++) {

			coords[i][j] = std::make_pair(xCenter - COORD_DIST_HALF + COORD_DIST * i, yCenter - COORD_DIST_HALF + COORD_DIST * j);
			setCoordDisplacement(coords[i][j]);
		}
	}
}

Block::Block(int xCenter, int yCenter, std::pair<int, int> topLeftCoord, 
	std::pair<int, int> topRightCoord,
	std::pair<int, int> botLeftCoord,
	std::pair<int, int> botRightCoord) : Drawable() {

	locX = xCenter;
	locY = yCenter;
	srand(locX + locY);

	std::pair<int, int> null_pair = std::make_pair(NULL, NULL);

	

	if (botLeftCoord == null_pair) {

		coords[0][0] = std::make_pair(xCenter - COORD_DIST_HALF, yCenter - COORD_DIST_HALF);
		setCoordDisplacement(coords[0][0]);
	}
	else
		coords[0][0] = botLeftCoord; 

	if (botRightCoord == null_pair) {

		coords[1][0] = std::make_pair(xCenter + COORD_DIST_HALF, yCenter - COORD_DIST_HALF);
		setCoordDisplacement(coords[1][0]);
	}
	else
		coords[1][0] = botRightCoord;

	if (topLeftCoord == null_pair) {

		coords[0][1] = std::make_pair(xCenter - COORD_DIST_HALF, yCenter + COORD_DIST_HALF);
		setCoordDisplacement(coords[0][1]);
	}
	else
		coords[0][1] = topLeftCoord;

	if (topRightCoord == null_pair) {

		coords[1][1] = std::make_pair(xCenter + COORD_DIST_HALF, yCenter + COORD_DIST_HALF);
		setCoordDisplacement(coords[1][1]);
	}
	else
		coords[1][1] = topRightCoord;

}

Block::~Block() {}

std::pair<int, int> Block::getTopLeftCoord() {

	return coords[0][1];
}

std::pair<int, int> Block::getTopRightCoord() {

	return coords[1][1];
}

std::pair<int, int> Block::getBotLeftCoord() {

	return coords[0][0];
}

std::pair<int, int> Block::getBotRightCoord() {

	return coords[1][0];
}

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


	// draw normals at block center
	glLineWidth(2.0);
	glBegin(GL_LINES);

	glVertex3i(locX, 0, locY);
	glVertex3i(locX, 50, locY);

	glEnd();

	


	glBegin(GL_QUADS);

	// west roads
	glVertex3i(coords[0][0].first, 0, coords[0][0].second);
	glVertex3i(coords[0][0].first + ROAD_WIDTH, 0, coords[0][0].second);

	glVertex3i(coords[0][1].first + ROAD_WIDTH, 0, coords[0][1].second);
	glVertex3i(coords[0][1].first, 0, coords[0][1].second);


	// north roads
	glVertex3i(coords[0][1].first, 0, coords[0][1].second);
	glVertex3i(coords[0][1].first, 0, coords[0][1].second - ROAD_WIDTH);

	glVertex3i(coords[1][1].first, 0, coords[1][1].second - ROAD_WIDTH);
	glVertex3i(coords[1][1].first, 0, coords[1][1].second);

	// east roads
	glVertex3i(coords[1][1].first, 0, coords[1][1].second);
	glVertex3i(coords[1][1].first - ROAD_WIDTH, 0, coords[1][1].second);

	glVertex3i(coords[1][0].first - ROAD_WIDTH, 0, coords[1][0].second);
	glVertex3i(coords[1][0].first, 0, coords[1][0].second);


	// south roads
	glVertex3i(coords[1][0].first, 0, coords[1][0].second);
	glVertex3i(coords[1][0].first, 0, coords[1][0].second + ROAD_WIDTH);

	glVertex3i(coords[0][0].first, 0, coords[0][0].second + ROAD_WIDTH);
	glVertex3i(coords[0][0].first, 0, coords[0][0].second);
	

	
	glEnd();

	// draw road lines
	
	glLineWidth(3.0);
	glColor3f(255.0f, 255.0f, 0.0f);

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(2, 0x00FF);

	glBegin(GL_LINES);
		
	glVertex3i(coords[0][0].first, 0, coords[0][0].second);
	glVertex3i(coords[0][1].first, 0, coords[0][1].second);

	glVertex3i(coords[0][0].first, 0, coords[0][0].second);
	glVertex3i(coords[1][0].first, 0, coords[1][0].second);

	glVertex3i(coords[1][0].first, 0, coords[1][0].second);
	glVertex3i(coords[1][1].first, 0, coords[1][1].second);

	glVertex3i(coords[1][1].first, 0, coords[1][1].second);
	glVertex3i(coords[0][1].first, 0, coords[0][1].second);

	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glPopMatrix();
}


void Block::update(UpdateData& data)
{
	//
}


void Block::setCoordDisplacement(std::pair<int, int>& coord ) {

	coord.first += rand() % COORD_DIST_HALF - COORD_DIST_QUARTER;
	coord.second += rand() % COORD_DIST_HALF - COORD_DIST_QUARTER;

}