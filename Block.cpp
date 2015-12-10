#include "Block.h"
#include "Building.h"
#include "Vector3.h"
#include "math.h"
#include "globals.h"
#include <stdlib.h>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define DEBUG_LINES 0

#define BLOCK_LENGTH 2
#define ROAD_WIDTH 15

#define BUILDING_START 35
#define SIDEWALK_WIDTH 10
#define SIDEWALK_HEIGHT 2
#define PLATFORM_HEIGHT SIDEWALK_HEIGHT + 1
#define BUILDING_LENGTH 40
#define COORD_DIST 400
#define COORD_DIST_HALF COORD_DIST / 2
#define COORD_DIST_QUARTER COORD_DIST / 4

#define TYPE_RANDOMNESS 15




Block::Block(int xCenter, int yCenter) : Drawable()
{

	locX = xCenter;
	locY = yCenter;
	/*srand(locX + locY);*/

	srand(xCenter);
	int xseed = rand();
	srand(yCenter);
	int zseed = rand();
	srand((xseed << 16) + zseed);

	for (int i = 0; i < BLOCK_LENGTH; i++) {
		for (int j = 0; j < BLOCK_LENGTH; j++) {

			coords[i][j] = std::make_pair(xCenter - COORD_DIST_HALF + COORD_DIST * i, yCenter - COORD_DIST_HALF + COORD_DIST * j);
			setCoordDisplacement(coords[i][j]);
		}
	}

	setRealCoords();
	setLineDistances();

	blockGrammar = rand() % 10;


	type = rand() % TYPE_RANDOMNESS;

	if (type == 0) {
		platformColor = Color(1.0f, 2.0f, 1.0f);
		generateTrees(inner_coords[0][0], northVec, northLineDist);
		generateTrees(inner_coords[0][1], eastVec, eastLineDist);
		generateTrees(inner_coords[1][1], southVec, southLineDist);
		generateTrees(inner_coords[1][0], westVec, westLineDist);
	}
	else {

		platformColor = Color(1.0f, 1.0f, 1.0f);
		generateBuildings(inner_coords[0][0], northVec, northLineDist);
		generateBuildings(inner_coords[0][1], eastVec, eastLineDist);
		generateBuildings(inner_coords[1][1], southVec, southLineDist);
		generateBuildings(inner_coords[1][0], westVec, westLineDist);
	}


	
}

Block::Block(int xCenter, int yCenter, std::pair<int, int> topLeftCoord, 
	std::pair<int, int> topRightCoord,
	std::pair<int, int> botLeftCoord,
	std::pair<int, int> botRightCoord) : Drawable() {

	locX = xCenter;
	locY = yCenter;
	/*srand(locX + locY);*/

	srand(xCenter);
	int xseed = rand();
	srand(yCenter);
	int zseed = rand();
	srand((xseed << 16) + zseed);

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

	blockGrammar = rand() % 10;

	type = rand() % TYPE_RANDOMNESS;

	if (type == 0) {
		platformColor = Color(1.0f, 2.0f, 1.0f);
		generateTrees(inner_coords[0][0], northVec, northLineDist);
		generateTrees(inner_coords[0][1], eastVec, eastLineDist);
		generateTrees(inner_coords[1][1], southVec, southLineDist);
		generateTrees(inner_coords[1][0], westVec, westLineDist);
	}
	else {

		platformColor = Color(1.0f, 1.0f, 1.0f);
		generateBuildings(inner_coords[0][0], northVec, northLineDist);
		generateBuildings(inner_coords[0][1], eastVec, eastLineDist);
		generateBuildings(inner_coords[1][1], southVec, southLineDist);
		generateBuildings(inner_coords[1][0], westVec, westLineDist);
	}

}

Block::~Block() {

	for (int i = 0; i < Buildings.size(); i++)
		delete Buildings[i];
}

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

	northLineDist = getDistanceBetweenPoints(inner_coords[0][0], inner_coords[0][1]);
	eastLineDist = getDistanceBetweenPoints(inner_coords[0][1], inner_coords[1][1]);
	southLineDist = getDistanceBetweenPoints(inner_coords[1][1], inner_coords[1][0]);
	westLineDist = getDistanceBetweenPoints(inner_coords[0][0], inner_coords[1][0]);
}

void Block::setRealCoords() {

	


	Vector3 vec00 = Vector3(coords[0][0].first, coords[0][0].second, 0);
	Vector3 vec01 = Vector3(coords[0][1].first, coords[0][1].second, 0);
	Vector3 vec10 = Vector3(coords[1][0].first, coords[1][0].second, 0);
	Vector3 vec11 = Vector3(coords[1][1].first, coords[1][1].second, 0);

	// find inner_coords[0][0]

	Vector3 adjVec1 = vec01 - vec00;
	Vector3 adjVec2 = vec10 - vec00;

	northVec = adjVec1 = adjVec1.normalize();
	adjVec1 = adjVec1.scale(ROAD_WIDTH + BUILDING_START);

	adjVec2 = adjVec2.normalize();
	adjVec2 = adjVec2.scale(ROAD_WIDTH + BUILDING_START);
	
	Vector3 vecFinal = vec00 + adjVec1 + adjVec2;

	inner_coords[0][0] = std::make_pair(vecFinal[0], vecFinal[1]);
 
	// find sidewalk_inner_coords[0][0]
	adjVec1 = vec01 - vec00;
	adjVec2 = vec10 - vec00;

	northVec = adjVec1 = adjVec1.normalize();
	adjVec1 = adjVec1.scale(ROAD_WIDTH + SIDEWALK_WIDTH);

	adjVec2 = adjVec2.normalize();
	adjVec2 = adjVec2.scale(ROAD_WIDTH + SIDEWALK_WIDTH);

	vecFinal = vec00 + adjVec1 + adjVec2;

	sidewalk_inner_coords[0][0] = std::make_pair(vecFinal[0], vecFinal[1]);


	// find sidewalk_outer_coords[0][0]

	adjVec1 = vec01 - vec00;
	adjVec2 = vec10 - vec00;

	adjVec1 = adjVec1.normalize();
	adjVec1 = adjVec1.scale(ROAD_WIDTH);

	adjVec2 = adjVec2.normalize();
	adjVec2 = adjVec2.scale(ROAD_WIDTH);

	vecFinal = vec00 + adjVec1 + adjVec2;

	sidewalk_outer_coords[0][0] = std::make_pair(vecFinal[0], vecFinal[1]);




	// find inner_coords[0][1]

	adjVec1 = vec00 - vec01;
	adjVec2 = vec11 - vec01;

	adjVec1 = adjVec1.normalize();
	adjVec1 = adjVec1.scale(ROAD_WIDTH + BUILDING_START);

	eastVec = adjVec2 = adjVec2.normalize();
	adjVec2 = adjVec2.scale(ROAD_WIDTH + BUILDING_START);

	vecFinal = vec01 + adjVec1 + adjVec2;

	inner_coords[0][1] = std::make_pair(vecFinal[0], vecFinal[1]);

	// find sidewalk_inner_coords[0][1]

	adjVec1 = vec00 - vec01;
	adjVec2 = vec11 - vec01;

	adjVec1 = adjVec1.normalize();
	adjVec1 = adjVec1.scale(ROAD_WIDTH + SIDEWALK_WIDTH);

	adjVec2 = adjVec2.normalize();
	adjVec2 = adjVec2.scale(ROAD_WIDTH + SIDEWALK_WIDTH);

	vecFinal = vec01 + adjVec1 + adjVec2;

	sidewalk_inner_coords[0][1] = std::make_pair(vecFinal[0], vecFinal[1]);

	// find sidewalk_outer_coords[0][1]

	adjVec1 = vec00 - vec01;
	adjVec2 = vec11 - vec01;

	adjVec1 = adjVec1.normalize();
	adjVec1 = adjVec1.scale(ROAD_WIDTH);

	eastVec = adjVec2 = adjVec2.normalize();
	adjVec2 = adjVec2.scale(ROAD_WIDTH);

	vecFinal = vec01 + adjVec1 + adjVec2;

	sidewalk_outer_coords[0][1] = std::make_pair(vecFinal[0], vecFinal[1]);



	// find inner_coords[1][0]

	adjVec1 = vec00 - vec10;
	adjVec2 = vec11 - vec10;

	westVec = adjVec1 = adjVec1.normalize();
	adjVec1 = adjVec1.scale(ROAD_WIDTH + BUILDING_START);

	adjVec2 = adjVec2.normalize();
	adjVec2 = adjVec2.scale(ROAD_WIDTH + BUILDING_START);

	vecFinal = vec10 + adjVec1 + adjVec2;

	inner_coords[1][0] = std::make_pair(vecFinal[0], vecFinal[1]);


	// find sidewalk_inner_coords[1][0]

	adjVec1 = vec00 - vec10;
	adjVec2 = vec11 - vec10;

	adjVec1 = adjVec1.normalize();
	adjVec1 = adjVec1.scale(ROAD_WIDTH + SIDEWALK_WIDTH);

	adjVec2 = adjVec2.normalize();
	adjVec2 = adjVec2.scale(ROAD_WIDTH + SIDEWALK_WIDTH);

	vecFinal = vec10 + adjVec1 + adjVec2;

	sidewalk_inner_coords[1][0] = std::make_pair(vecFinal[0], vecFinal[1]);

	// find sidewalk_outer_coords[1][0]

	adjVec1 = vec00 - vec10;
	adjVec2 = vec11 - vec10;

	westVec = adjVec1 = adjVec1.normalize();
	adjVec1 = adjVec1.scale(ROAD_WIDTH);

	adjVec2 = adjVec2.normalize();
	adjVec2 = adjVec2.scale(ROAD_WIDTH);

	vecFinal = vec10 + adjVec1 + adjVec2;

	sidewalk_outer_coords[1][0] = std::make_pair(vecFinal[0], vecFinal[1]);

	// find inner_coords[1][1]

	adjVec1 = vec01 - vec11;
	adjVec2 = vec10 - vec11;

	adjVec1 = adjVec1.normalize();
	adjVec1 = adjVec1.scale(ROAD_WIDTH + BUILDING_START);

	southVec = adjVec2 = adjVec2.normalize();
	adjVec2 = adjVec2.scale(ROAD_WIDTH + BUILDING_START);

	vecFinal = vec11 + adjVec1 + adjVec2;

	inner_coords[1][1] = std::make_pair(vecFinal[0], vecFinal[1]);

	// find sidewalk_inner_coords[1][1]

	adjVec1 = vec01 - vec11;
	adjVec2 = vec10 - vec11;

	adjVec1 = adjVec1.normalize();
	adjVec1 = adjVec1.scale(ROAD_WIDTH + SIDEWALK_WIDTH);

	adjVec2 = adjVec2.normalize();
	adjVec2 = adjVec2.scale(ROAD_WIDTH + SIDEWALK_WIDTH);

	vecFinal = vec11 + adjVec1 + adjVec2;

	sidewalk_inner_coords[1][1] = std::make_pair(vecFinal[0], vecFinal[1]);

	// find sidewalk_outer_coords[1][1]

	adjVec1 = vec01 - vec11;
	adjVec2 = vec10 - vec11;

	adjVec1 = adjVec1.normalize();
	adjVec1 = adjVec1.scale(ROAD_WIDTH);

	southVec = adjVec2 = adjVec2.normalize();
	adjVec2 = adjVec2.scale(ROAD_WIDTH);

	vecFinal = vec11 + adjVec1 + adjVec2;

	sidewalk_outer_coords[1][1] = std::make_pair(vecFinal[0], vecFinal[1]);

	/* set road line coords */
	// find south_road_coords
	Vector3 directionalVec = northVec.normalize();
	directionalVec = directionalVec.scale(ROAD_WIDTH);

	Vector3 coord1 = Vector3(directionalVec[0] + coords[0][0].first, directionalVec[1] + coords[0][0].second, 0);

	directionalVec = directionalVec.scale(-1);
	Vector3 coord2 = Vector3(directionalVec[0] + coords[0][1].first, directionalVec[1] + coords[0][1].second, 0);

	south_road_coords[0] = std::make_pair(coord1[0], coord1[1]);
	south_road_coords[1] = std::make_pair(coord2[0], coord2[1]);

	// find east_road_coords

	directionalVec = eastVec.normalize();
	directionalVec = directionalVec.scale(ROAD_WIDTH);

	coord1 = Vector3(directionalVec[0] + coords[0][1].first, directionalVec[1] + coords[0][1].second, 0);
	
	directionalVec = directionalVec.scale(-1);

	coord2 = Vector3(directionalVec[0] + coords[1][1].first, directionalVec[1] + coords[1][1].second, 0);

	east_road_coords[0] = std::make_pair(coord1[0], coord1[1]);
	east_road_coords[1] = std::make_pair(coord2[0], coord2[1]);

	// find north_road_coords

	directionalVec = southVec.normalize();
	directionalVec = directionalVec.scale(ROAD_WIDTH);

	coord1 = Vector3(directionalVec[0] + coords[1][1].first, directionalVec[1] + coords[1][1].second, 0);

	directionalVec = directionalVec.scale(-1);

	coord2 = Vector3(directionalVec[0] + coords[1][0].first, directionalVec[1] + coords[1][0].second, 0);

	north_road_coords[0] = std::make_pair(coord1[0], coord1[1]);
	north_road_coords[1] = std::make_pair(coord2[0], coord2[1]);

	// find west_road_coords

	directionalVec = westVec.normalize();
	directionalVec = directionalVec.scale(ROAD_WIDTH);

	coord1 = Vector3(directionalVec[0] + coords[1][0].first, directionalVec[1] + coords[1][0].second, 0);

	directionalVec = directionalVec.scale(-1);

	coord2 = Vector3(directionalVec[0] + coords[0][0].first, directionalVec[1] + coords[0][0].second, 0);

	west_road_coords[0] = std::make_pair(coord1[0], coord1[1]);
	west_road_coords[1] = std::make_pair(coord2[0], coord2[1]);
}


void Block::generateBuildings(std::pair<float, float> start, Vector3 direction, double distance) {


	int quantity = distance / BUILDING_LENGTH;

	Vector3 startVector = Vector3(start.first, start.second, 0) + direction.scale(20);

	Vector3 normal = Matrix4().makeRotateZ(3.14 / 2) * direction;
	float diff = Vector3(0, 1, 0).angle(normal);
	Matrix4 rotation;

	if (normal[0] < 0)
		rotation = Matrix4().makeRotateY(-diff);
	else
		rotation = Matrix4().makeRotateY(diff);

	direction = direction.scale(distance / quantity);

	for (int i = 0; i < quantity - 1; i++) {

		Vector3 loc = startVector + direction * (i + 0.5);

		Buildings.push_back(new Building(loc[0], loc[1], rotation, blockGrammar));
	}

	Vector3 loc = startVector + direction * (quantity - 0.5);
	rotation = Matrix4().makeRotateY(3.14 / 4) * rotation;
	Buildings.push_back(new Building(loc[0], loc[1], rotation, blockGrammar));


}

void Block::generateTrees(std::pair<float, float> start, Vector3 direction, double distance)
{
	int quantity = distance / 30;

	Vector3 startVector = Vector3(start.first, start.second, 0) + direction.scale(20);

	direction = direction.scale(distance / quantity);

	for (int i = 0; i < quantity; i++) {

		Vector3 loc = startVector + direction * (i);

		Trees.push_back(new LSystemTree(Vector3(loc[0], 0, loc[1]), Vector3(0, 9, 0), Matrix4().makeRotateZ(0), 1.2));
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

			glVertex3i(coords[i][j].first, 0, coords[i][j].second);
		}
	}
	glEnd();


	Color oldColor = material.color;
	material.color = Color().grey();
	material.apply();

	/* draw roads*/
	{
		//glColor3f(2.0f, 2.0f, 2.0f);
		glBegin(GL_QUADS);

		// west roads
		glNormal3i(0, 1, 0);
		glVertex3i(coords[0][0].first, 0, coords[0][0].second);
		glNormal3i(0, 1, 0);
		glVertex3i(coords[0][0].first + ROAD_WIDTH + 3, 0, coords[0][0].second);
		glNormal3i(0, 1, 0);
		glVertex3i(coords[0][1].first + ROAD_WIDTH + 3, 0, coords[0][1].second);
		glNormal3i(0, 1, 0);
		glVertex3i(coords[0][1].first, 0, coords[0][1].second);


		// north roads
		glNormal3i(0, 1, 0);
		glVertex3i(coords[0][1].first, 0, coords[0][1].second);
		glNormal3i(0, 1, 0);
		glVertex3i(coords[0][1].first, 0, coords[0][1].second - ROAD_WIDTH - 3);
		glNormal3i(0, 1, 0);
		glVertex3i(coords[1][1].first, 0, coords[1][1].second - ROAD_WIDTH - 3);
		glNormal3i(0, 1, 0);
		glVertex3i(coords[1][1].first, 0, coords[1][1].second);

		// east roads
		glNormal3i(0, 1, 0);
		glVertex3i(coords[1][1].first, 0, coords[1][1].second);
		glNormal3i(0, 1, 0);
		glVertex3i(coords[1][1].first - ROAD_WIDTH - 3, 0, coords[1][1].second);
		glNormal3i(0, 1, 0);
		glVertex3i(coords[1][0].first - ROAD_WIDTH - 3, 0, coords[1][0].second);
		glNormal3i(0, 1, 0);
		glVertex3i(coords[1][0].first, 0, coords[1][0].second);


		// south roads
		glNormal3i(0, 1, 0);
		glVertex3i(coords[1][0].first, 0, coords[1][0].second);
		glNormal3i(0, 1, 0);
		glVertex3i(coords[1][0].first, 0, coords[1][0].second + ROAD_WIDTH + 3);
		glNormal3i(0, 1, 0);
		glVertex3i(coords[0][0].first, 0, coords[0][0].second + ROAD_WIDTH + 3);
		glNormal3i(0, 1, 0);
		glVertex3i(coords[0][0].first, 0, coords[0][0].second);



		glEnd();
	}
	material.color = oldColor;

	/* draw road lines */

	{
		glLineWidth(3.0);
		glColor3f(255.0f, 255.0f, 0.0f);

		glEnable(GL_LINE_STIPPLE);
		glLineStipple(2, 0x00FF);

		glBegin(GL_LINES);

		/*glVertex3i(south_road_coords[0].first, 0, south_road_coords[0].second);
		glVertex3i(south_road_coords[1].first, 0, south_road_coords[1].second);

		glVertex3i(north_road_coords[0].first, 0, north_road_coords[0].second);
		glVertex3i(north_road_coords[1].first, 0, north_road_coords[1].second);

		glVertex3i(east_road_coords[0].first, 0, east_road_coords[0].second);
		glVertex3i(east_road_coords[1].first, 0, east_road_coords[1].second);

		glVertex3i(west_road_coords[0].first, 0, west_road_coords[0].second);
		glVertex3i(west_road_coords[1].first, 0, west_road_coords[1].second);
		*/





		
		glVertex3i(coords[0][1].first, 0, coords[0][1].second);
		glVertex3i(coords[0][0].first, 0, coords[0][0].second);

		glVertex3i(coords[0][0].first, 0, coords[0][0].second);
		glVertex3i(coords[1][0].first, 0, coords[1][0].second);

		glVertex3i(coords[1][0].first, 0, coords[1][0].second);
		glVertex3i(coords[1][1].first, 0, coords[1][1].second);

		glVertex3i(coords[1][1].first, 0, coords[1][1].second);
		glVertex3i(coords[0][1].first, 0, coords[0][1].second);

		glEnd();
		glDisable(GL_LINE_STIPPLE);
	}


	/* draw block platform */
	{
		glBegin(GL_QUADS);


		glColor3f(platformColor[0], platformColor[1], platformColor[2]);
		// draw top
		glNormal3i(0, 1, 0);
		glVertex3i(sidewalk_inner_coords[0][0].first, PLATFORM_HEIGHT, sidewalk_inner_coords[0][0].second);
		glVertex3i(sidewalk_inner_coords[0][1].first, PLATFORM_HEIGHT, sidewalk_inner_coords[0][1].second);
		glVertex3i(sidewalk_inner_coords[1][1].first, PLATFORM_HEIGHT, sidewalk_inner_coords[1][1].second);
		glVertex3i(sidewalk_inner_coords[1][0].first, PLATFORM_HEIGHT, sidewalk_inner_coords[1][0].second);

		glColor3f(1.0f, 255.0f, 1.0f);
		// draw base
		glNormal3i(0, 1, 0);
		glVertex3i(coords[0][0].first, -1, coords[0][0].second);
		glVertex3i(coords[0][1].first, -1, coords[0][1].second);
		glVertex3i(coords[1][1].first, -1, coords[1][1].second);
		glVertex3i(coords[1][0].first, -1, coords[1][0].second);

		// draw sides
		glColor3f(platformColor[0], platformColor[1], platformColor[2]);

		// draw east
		//glNormal3i(0, 1, 0);
		glVertex3i(sidewalk_inner_coords[0][0].first, PLATFORM_HEIGHT, sidewalk_inner_coords[0][0].second);
		glVertex3i(sidewalk_inner_coords[0][1].first, PLATFORM_HEIGHT, sidewalk_inner_coords[0][1].second);
		glVertex3i(sidewalk_inner_coords[0][1].first, 0, sidewalk_inner_coords[0][1].second);
		glVertex3i(sidewalk_inner_coords[0][0].first, 0, sidewalk_inner_coords[0][0].second);




		//draw north
		glVertex3i(sidewalk_inner_coords[0][1].first, PLATFORM_HEIGHT, sidewalk_inner_coords[0][1].second);
		glVertex3i(sidewalk_inner_coords[1][1].first, PLATFORM_HEIGHT, sidewalk_inner_coords[1][1].second);
		glVertex3i(sidewalk_inner_coords[1][1].first, 0, sidewalk_inner_coords[1][1].second);
		glVertex3i(sidewalk_inner_coords[0][1].first, 0, sidewalk_inner_coords[0][1].second);




		//draw east
		glVertex3i(sidewalk_inner_coords[1][1].first, PLATFORM_HEIGHT, sidewalk_inner_coords[1][1].second);
		glVertex3i(sidewalk_inner_coords[1][0].first, PLATFORM_HEIGHT, sidewalk_inner_coords[1][0].second);
		glVertex3i(sidewalk_inner_coords[1][0].first, 0, sidewalk_inner_coords[1][0].second);
		glVertex3i(sidewalk_inner_coords[1][1].first, 0, sidewalk_inner_coords[1][1].second);




		//draw south
		glVertex3i(sidewalk_inner_coords[1][0].first, PLATFORM_HEIGHT, sidewalk_inner_coords[1][0].second);
		glVertex3i(sidewalk_inner_coords[0][0].first, PLATFORM_HEIGHT, sidewalk_inner_coords[0][0].second);
		glVertex3i(sidewalk_inner_coords[0][0].first, 0, sidewalk_inner_coords[0][0].second);
		glVertex3i(sidewalk_inner_coords[1][0].first, 0, sidewalk_inner_coords[1][0].second);


		glEnd();

	}

	/*draw sidewalk*/

	{
		glColor3f(3.0f, 3.0f, 3.0f);

		glBegin(GL_QUADS);
		//south sidewalk top
		glNormal3f(0, 1, 0);
		glVertex3i(sidewalk_outer_coords[0][0].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[0][0].second);
		glVertex3i(sidewalk_outer_coords[1][0].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[1][0].second);
		glVertex3i(sidewalk_inner_coords[1][0].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[1][0].second);
		glVertex3i(sidewalk_inner_coords[0][0].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[0][0].second);

		//west sidewalk top
		glNormal3f(0, 1, 0);
		glVertex3i(sidewalk_outer_coords[1][0].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[1][0].second);
		glVertex3i(sidewalk_outer_coords[1][1].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[1][1].second);
		glVertex3i(sidewalk_inner_coords[1][1].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[1][1].second);
		glVertex3i(sidewalk_inner_coords[1][0].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[1][0].second);

		//north sidewalk top
		glNormal3f(0, 1, 0);
		glVertex3i(sidewalk_outer_coords[1][1].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[1][1].second);
		glVertex3i(sidewalk_outer_coords[0][1].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[0][1].second);
		glVertex3i(sidewalk_inner_coords[0][1].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[0][1].second);
		glVertex3i(sidewalk_inner_coords[1][1].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[1][1].second);

		//east sidewalk top
		glNormal3f(0, 1, 0);
		glVertex3i(sidewalk_outer_coords[0][1].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[0][1].second);
		glVertex3i(sidewalk_outer_coords[0][0].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[0][0].second);
		glVertex3i(sidewalk_inner_coords[0][0].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[0][0].second);
		glVertex3i(sidewalk_inner_coords[0][1].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[0][1].second);

		// south vertical
		glNormal3f(0, 0, -1);
		glVertex3i(sidewalk_outer_coords[0][0].first, 0, sidewalk_outer_coords[0][0].second);
		glVertex3i(sidewalk_outer_coords[1][0].first, 0, sidewalk_outer_coords[1][0].second);
		glVertex3i(sidewalk_outer_coords[1][0].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[1][0].second);
		glVertex3i(sidewalk_outer_coords[0][0].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[0][0].second);

		// east vertical
		glNormal3f(1, 0, 0);
		glVertex3i(sidewalk_outer_coords[1][0].first, 0, sidewalk_outer_coords[1][0].second);
		glVertex3i(sidewalk_outer_coords[1][1].first, 0, sidewalk_outer_coords[1][1].second);
		glVertex3i(sidewalk_outer_coords[1][1].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[1][1].second);
		glVertex3i(sidewalk_outer_coords[1][0].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[1][0].second);

		// north vertical
		glNormal3f(0, 0, 1);
		glVertex3i(sidewalk_outer_coords[1][1].first, 0, sidewalk_outer_coords[1][1].second);
		glVertex3i(sidewalk_outer_coords[0][1].first, 0, sidewalk_outer_coords[0][1].second);
		glVertex3i(sidewalk_outer_coords[0][1].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[0][1].second);
		glVertex3i(sidewalk_outer_coords[1][1].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[1][1].second);

		// west vertical
		glNormal3f(-1, 0, 0);
		glVertex3i(sidewalk_outer_coords[0][1].first, 0, sidewalk_outer_coords[0][1].second);
		glVertex3i(sidewalk_outer_coords[0][0].first, 0, sidewalk_outer_coords[0][0].second);
		glVertex3i(sidewalk_outer_coords[0][0].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[0][0].second);
		glVertex3i(sidewalk_outer_coords[0][1].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[0][1].second);

		material.color = oldColor;
	}
	glEnd();





	glBegin(GL_LINES);


	/* sidewalk lines */

	// outer lines
	{
		glColor3f(0.0f, 0.0f, 0.0f);

		glLineWidth(1.0);


		glVertex3i(sidewalk_outer_coords[0][0].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[0][0].second);
		glVertex3i(sidewalk_outer_coords[0][1].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[0][1].second);

		glVertex3i(sidewalk_outer_coords[0][1].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[0][1].second);
		glVertex3i(sidewalk_outer_coords[1][1].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[1][1].second);

		glVertex3i(sidewalk_outer_coords[1][1].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[1][1].second);
		glVertex3i(sidewalk_outer_coords[1][0].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[1][0].second);

		glVertex3i(sidewalk_outer_coords[1][0].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[1][0].second);
		glVertex3i(sidewalk_outer_coords[0][0].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[0][0].second);
	}

	//inner lines
	{
		glVertex3i(sidewalk_inner_coords[0][0].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[0][0].second);
		glVertex3i(sidewalk_inner_coords[0][1].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[0][1].second);

		glVertex3i(sidewalk_inner_coords[0][1].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[0][1].second);
		glVertex3i(sidewalk_inner_coords[1][1].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[1][1].second);

		glVertex3i(sidewalk_inner_coords[1][1].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[1][1].second);
		glVertex3i(sidewalk_inner_coords[1][0].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[1][0].second);

		glVertex3i(sidewalk_inner_coords[1][0].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[1][0].second);
		glVertex3i(sidewalk_inner_coords[0][0].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[0][0].second);
	}

	// 00 corner
	glVertex3i(sidewalk_outer_coords[0][0].first, 0, sidewalk_outer_coords[0][0].second);
	glVertex3i(sidewalk_outer_coords[0][0].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[0][0].second);

	// 01 corner
	glVertex3i(sidewalk_outer_coords[0][1].first, 0, sidewalk_outer_coords[0][1].second);
	glVertex3i(sidewalk_outer_coords[0][1].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[0][1].second);

	// 11 corner
	glVertex3i(sidewalk_outer_coords[1][1].first, 0, sidewalk_outer_coords[1][1].second);
	glVertex3i(sidewalk_outer_coords[1][1].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[1][1].second);

	// 10 corner
	glVertex3i(sidewalk_outer_coords[1][0].first, 0, sidewalk_outer_coords[1][0].second);
	glVertex3i(sidewalk_outer_coords[1][0].first, SIDEWALK_HEIGHT, sidewalk_outer_coords[1][0].second);



	/* platform lines */
	{
		// upper lines
		glVertex3i(sidewalk_inner_coords[0][0].first, PLATFORM_HEIGHT, sidewalk_inner_coords[0][0].second);
		glVertex3i(sidewalk_inner_coords[0][1].first, PLATFORM_HEIGHT, sidewalk_inner_coords[0][1].second);

		glVertex3i(sidewalk_inner_coords[0][1].first, PLATFORM_HEIGHT, sidewalk_inner_coords[0][1].second);
		glVertex3i(sidewalk_inner_coords[1][1].first, PLATFORM_HEIGHT, sidewalk_inner_coords[1][1].second);

		glVertex3i(sidewalk_inner_coords[1][1].first, PLATFORM_HEIGHT, sidewalk_inner_coords[1][1].second);
		glVertex3i(sidewalk_inner_coords[1][0].first, PLATFORM_HEIGHT, sidewalk_inner_coords[1][0].second);

		glVertex3i(sidewalk_inner_coords[1][0].first, PLATFORM_HEIGHT, sidewalk_inner_coords[1][0].second);
		glVertex3i(sidewalk_inner_coords[0][0].first, PLATFORM_HEIGHT, sidewalk_inner_coords[0][0].second);

		// 00 corner
		glVertex3i(sidewalk_inner_coords[0][0].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[0][0].second);
		glVertex3i(sidewalk_inner_coords[0][0].first, PLATFORM_HEIGHT, sidewalk_inner_coords[0][0].second);

		// 01 corner
		glVertex3i(sidewalk_inner_coords[0][1].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[0][1].second);
		glVertex3i(sidewalk_inner_coords[0][1].first, PLATFORM_HEIGHT, sidewalk_inner_coords[0][1].second);

		// 11 corner
		glVertex3i(sidewalk_inner_coords[1][1].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[1][1].second);
		glVertex3i(sidewalk_inner_coords[1][1].first, PLATFORM_HEIGHT, sidewalk_inner_coords[1][1].second);

		// 10 corner
		glVertex3i(sidewalk_inner_coords[1][0].first, SIDEWALK_HEIGHT, sidewalk_inner_coords[1][0].second);
		glVertex3i(sidewalk_inner_coords[1][0].first, PLATFORM_HEIGHT, sidewalk_inner_coords[1][0].second);


	}



	/*************************************/
	/*                                   */
	/*           DEBUG LINES             */
	/*                                   */
	/*************************************/
	
	if (DEBUG_LINES)
	{
		glColor3f(255.0f, 0.0f, 255.0f);
		glLineWidth(2.0);
		// draw normals at block center
		glVertex3i(locX, 0, locY);
		glVertex3i(locX, 100, locY);

		// inner coords lines
		glVertex3f(inner_coords[0][0].first, 0, inner_coords[0][0].second);
		glVertex3f(inner_coords[0][0].first, 50, inner_coords[0][0].second);

		glVertex3f(inner_coords[0][1].first, 0, inner_coords[0][1].second);
		glVertex3f(inner_coords[0][1].first, 50, inner_coords[0][1].second);

		glVertex3f(inner_coords[1][0].first, 0, inner_coords[1][0].second);
		glVertex3f(inner_coords[1][0].first, 50, inner_coords[1][0].second);

		glVertex3f(inner_coords[1][1].first, 0, inner_coords[1][1].second);
		glVertex3f(inner_coords[1][1].first, 50, inner_coords[1][1].second);


		// block coords lines
		glVertex3i(coords[0][0].first, 0, coords[0][0].second);
		glVertex3i(coords[0][0].first, 75, coords[0][0].second);

		glVertex3i(coords[0][1].first, 0, coords[0][1].second);
		glVertex3i(coords[0][1].first, 75, coords[0][1].second);

		glVertex3i(coords[1][0].first, 0, coords[1][0].second);
		glVertex3i(coords[1][0].first, 75, coords[1][0].second);

		glVertex3i(coords[1][1].first, 0, coords[1][1].second);
		glVertex3i(coords[1][1].first, 75, coords[1][1].second);


		// inner_sidewalk coords lines
		glVertex3i(sidewalk_inner_coords[0][0].first, 0, sidewalk_inner_coords[0][0].second);
		glVertex3i(sidewalk_inner_coords[0][0].first, 10, sidewalk_inner_coords[0][0].second);

		glVertex3i(sidewalk_inner_coords[0][1].first, 0, sidewalk_inner_coords[0][1].second);
		glVertex3i(sidewalk_inner_coords[0][1].first, 10, sidewalk_inner_coords[0][1].second);

		glVertex3i(sidewalk_inner_coords[1][0].first, 0, sidewalk_inner_coords[1][0].second);
		glVertex3i(sidewalk_inner_coords[1][0].first, 10, sidewalk_inner_coords[1][0].second);

		glVertex3i(sidewalk_inner_coords[1][1].first, 0, sidewalk_inner_coords[1][1].second);
		glVertex3i(sidewalk_inner_coords[1][1].first, 10, sidewalk_inner_coords[1][1].second);

		// outer_sidewalk coords lines
		glVertex3i(sidewalk_outer_coords[0][0].first, 0, sidewalk_outer_coords[0][0].second);
		glVertex3i(sidewalk_outer_coords[0][0].first, 10, sidewalk_outer_coords[0][0].second);

		glVertex3i(sidewalk_outer_coords[0][1].first, 0, sidewalk_outer_coords[0][1].second);
		glVertex3i(sidewalk_outer_coords[0][1].first, 10, sidewalk_outer_coords[0][1].second);

		glVertex3i(sidewalk_outer_coords[1][0].first, 0, sidewalk_outer_coords[1][0].second);
		glVertex3i(sidewalk_outer_coords[1][0].first, 10, sidewalk_outer_coords[1][0].second);

		glVertex3i(sidewalk_outer_coords[1][1].first, 0, sidewalk_outer_coords[1][1].second);
		glVertex3i(sidewalk_outer_coords[1][1].first, 10, sidewalk_outer_coords[1][1].second);

	}
	


	

	glEnd();

	for (int i = 0; i < Buildings.size(); i++) {

		Buildings[i]->draw(data);
	}

	for (int i = 0;i < Trees.size(); i++)
	{
		Trees[i]->draw(data);
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