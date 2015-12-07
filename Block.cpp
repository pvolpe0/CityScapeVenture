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
#define COORD_DIST_HALF COORD_DIST / 2
#define COORD_DIST_QUARTER COORD_DIST / 4

// line color
#define LINE_RED 242
#define LINE_GREEN 223
#define LINE_BLUE 94


Block::Block(int xCenter, int yCenter) : Drawable()
{

	lineColor = Color::Color(LINE_RED, LINE_GREEN, LINE_BLUE);

	locX = xCenter;
	locY = yCenter;

	for (int i = 0; i < BLOCK_LENGTH; i++) {
		for (int j = 0; j < BLOCK_LENGTH; j++) {

			coords[i][j] = std::make_pair(xCenter - 100 + 200 * i, yCenter - 100 + 200 * j);
		}
	}
	
	srand(locX + locY);
	
	setCoordDisplacement(coords[0][0]);
	setCoordDisplacement(coords[0][1]);
	setCoordDisplacement(coords[1][0]);
	setCoordDisplacement(coords[1][1]);

}

Block::Block(int xCenter, int yCenter, std::pair<int, int> topLeftCoord, 
	std::pair<int, int> topRightCoord,
	std::pair<int, int> botLeftCoord,
	std::pair<int, int> botRightCoord) : Drawable() {

	locX = xCenter;
	locY = yCenter;

	std::pair<int, int> null_pair = std::make_pair(NULL, NULL);

	srand(locX + locY);

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

			//std::cout << "row: " << i << " col: " << j << " x: " << coords[i][j].first << " y: " << coords[i][j].second << std::endl;
			glVertex3i(coords[i][j].first, 0, coords[i][j].second );
		}
	}
	glEnd();


	// draw normals
	glLineWidth(2.0);
	glBegin(GL_LINES);

	glVertex3i(locX, 0, locY);
	glVertex3i(locX, 50, locY);

	glEnd();

	

	
	glColor3fv(lineColor.ptr());
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
	

	glPopMatrix();
}


void Block::update(UpdateData& data)
{
	//
}


void Block::setCoordDisplacement(std::pair<int, int>& coord1 ) {

	

	std::cout << "initial x: " << coord1.first << " initial y: " << coord1.second << std::endl;

	coord1.first += rand() % COORD_DIST_HALF - COORD_DIST_QUARTER;
	coord1.second += rand() % COORD_DIST_HALF - COORD_DIST_QUARTER;

	std::cout << "new x: " << coord1.first << " new y: " << coord1.second << std::endl;

	/*for (int i = 0; i < BLOCK_LENGTH; i++) {
		for (int j = 0; j < BLOCK_LENGTH; j++) {

			coords[i][j].first += rand() % COORD_DIST_HALF;
			coords[i][j].second += rand() % COORD_DIST_HALF;

		}
	}*/

}