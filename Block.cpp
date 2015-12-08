#include "Block.h"
#include "Building.h"
#include "Vector3.h"
#include "math.h"
#include <stdlib.h>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define BLOCK_LENGTH 2
#define ROAD_WIDTH 15
#define BUILDING_LENGTH 40
#define COORD_DIST 200
#define COORD_DIST_HALF COORD_DIST / 2
#define COORD_DIST_QUARTER COORD_DIST / 4

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

	setRealCoords();
	setLineDistances();


	generateBuildings(inner_coords[0][1], northVec, northLineDist);
	
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


	setRealCoords();
	setLineDistances();

	generateBuildings(inner_coords[0][0], westVec, westLineDist);
	generateBuildings(inner_coords[0][1], northVec, northLineDist);
	generateBuildings(inner_coords[1][1], eastVec, eastLineDist);
	generateBuildings(inner_coords[1][0], southVec, southLineDist);

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

double Block::getDistanceBetweenPoints(std::pair<int, int> coord1, std::pair<int, int> coord2) {

	int x0 = coord1.first;
	int x1 = coord2.first;
	int y0 = coord1.second;
	int y1 = coord2.second;

	return sqrt( pow((x1 - x0), 2) + pow((y1 - y0), 2) );
}

void Block::setLineDistances() {

	westLineDist = getDistanceBetweenPoints(inner_coords[0][0], inner_coords[0][1]);
	northLineDist = getDistanceBetweenPoints(inner_coords[0][1], inner_coords[1][1]);
	eastLineDist = getDistanceBetweenPoints(inner_coords[1][1], inner_coords[1][0]);
	southLineDist = getDistanceBetweenPoints(inner_coords[0][0], inner_coords[1][0]);
}

void Block::setRealCoords() {

	


	Vector3 vec00 = Vector3(coords[0][0].first, coords[0][0].second, 0);
	Vector3 vec01 = Vector3(coords[0][1].first, coords[0][1].second, 0);
	Vector3 vec10 = Vector3(coords[1][0].first, coords[1][0].second, 0);
	Vector3 vec11 = Vector3(coords[1][1].first, coords[1][1].second, 0);

	// find inner_coords[0][0]

	Vector3 adjVec1 = vec01 - vec00;
	Vector3 adjVec2 = vec10 - vec00;

	westVec = adjVec1 = adjVec1.normalize();
	adjVec1 = adjVec1.scale(ROAD_WIDTH + 20);

	adjVec2 = adjVec2.normalize();
	adjVec2 = adjVec2.scale(ROAD_WIDTH + 20);
	
	Vector3 vecFinal = vec00 + adjVec1 + adjVec2;



	inner_coords[0][0] = std::make_pair(vecFinal[0], vecFinal[1]);

	// find inner_coords[0][1]

	adjVec1 = vec00 - vec01;
	adjVec2 = vec11 - vec01;

	northVec = adjVec1 = adjVec1.normalize();
	adjVec1 = adjVec1.scale(ROAD_WIDTH + 20);

	adjVec2 = adjVec2.normalize();
	adjVec2 = adjVec2.scale(ROAD_WIDTH + 20);

	vecFinal = vec01 + adjVec1 + adjVec2;

	inner_coords[0][1] = std::make_pair(vecFinal[0], vecFinal[1]);

	// find inner_coords[1][0]

	adjVec1 = vec00 - vec10;
	adjVec2 = vec11 - vec10;

	southVec = adjVec1 = adjVec1.normalize();
	adjVec1 = adjVec1.scale(ROAD_WIDTH + 20);

	adjVec2 = adjVec2.normalize();
	adjVec2 = adjVec2.scale(ROAD_WIDTH + 20);

	vecFinal = vec10 + adjVec1 + adjVec2;

	inner_coords[1][0] = std::make_pair(vecFinal[0], vecFinal[1]);

	// find inner_coords[1][1]

	adjVec1 = vec01 - vec11;
	adjVec2 = vec10 - vec11;

	eastVec = adjVec1 = adjVec1.normalize();
	adjVec1 = adjVec1.scale(ROAD_WIDTH + 20);

	adjVec2 = adjVec2.normalize();
	adjVec2 = adjVec2.scale(ROAD_WIDTH + 20);

	vecFinal = vec11 + adjVec1 + adjVec2;

	inner_coords[1][1] = std::make_pair(vecFinal[0], vecFinal[1]);

}


void Block::generateBuildings(std::pair<float, float> start, Vector3 direction, double distance) {


	int quantity = distance / BUILDING_LENGTH;

	Vector3 startVector = Vector3(start.first, start.second, 0) + direction.scale(20);

	direction = direction.scale(BUILDING_LENGTH);

	for (int i = 0; i < quantity; i++) {

		Vector3 loc = startVector + direction * i;

		Buildings.push_back(new Building(loc[0], loc[1], Matrix4().makeRotateY(0), 0));
	}

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


	// draw helper lines
	glColor3f(255.0f, 0.0f, 255.0f);
	glLineWidth(2.0);
	glBegin(GL_LINES);

	// draw normals at block center
	glVertex3i(locX, 0, locY);
	glVertex3i(locX, 100, locY);

	// inner coords lines
	glVertex3f(inner_coords[0][0].first, 0, inner_coords[0][0].second);
	glVertex3f(inner_coords[0][0].first, 25, inner_coords[0][0].second);

	glVertex3f(inner_coords[0][1].first, 0, inner_coords[0][1].second);
	glVertex3f(inner_coords[0][1].first, 25, inner_coords[0][1].second);

	glVertex3f(inner_coords[1][0].first, 0, inner_coords[1][0].second);
	glVertex3f(inner_coords[1][0].first, 25, inner_coords[1][0].second);

	glVertex3f(inner_coords[1][1].first, 0, inner_coords[1][1].second);
	glVertex3f(inner_coords[1][1].first, 25, inner_coords[1][1].second);


	// block coords lines
	glVertex3i(coords[0][0].first, 0, coords[0][0].second);
	glVertex3i(coords[0][0].first, 50, coords[0][0].second);

	glVertex3i(coords[0][1].first, 0, coords[0][1].second);
	glVertex3i(coords[0][1].first, 50, coords[0][1].second);

	glVertex3i(coords[1][0].first, 0, coords[1][0].second);
	glVertex3i(coords[1][0].first, 50, coords[1][0].second);

	glVertex3i(coords[1][1].first, 0, coords[1][1].second);
	glVertex3i(coords[1][1].first, 50, coords[1][1].second);



	glEnd();

	for (int i = 0; i < Buildings.size(); i++) {

		Buildings[i]->draw(data);
	}


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