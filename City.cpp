#include "City.h"
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define CITY_LENGTH 5
#define BLOCK_DIST 200

City::City() : Drawable()
{
	// create starting block
	blocks[0][0] = new Block(-400, -400);

	// generate first row of blocks
	for (int i = 0; i < CITY_LENGTH; i++) {
		generateSingleEast(0, i, blocks[0][i]->getTopRightCoord(), blocks[0][i]->getBotRightCoord());
	}
	

	// generate rows
	generateRowNorth(0);
	generateRowNorth(1);
	generateRowNorth(2);
	generateRowNorth(3);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++){

			std::cout << "block[" << i << "][" << j << "] | (x,y) : ( " << blocks[i][j]->locX << "," << blocks[i][j]->locY << ")" << std::endl;
		}
	}

}


City::~City() {}

void City::generateSingleEast(int row, int col, std::pair<int, int> topCoord, std::pair<int, int> botCoord){

	int newXLoc = blocks[row][col]->locX + BLOCK_DIST;
	int newYLoc = blocks[row][col]->locY;

	blocks[row][col + 1] = new Block(newXLoc, newYLoc, topCoord,
													   std::make_pair<int, int>(NULL, NULL),
													   botCoord,
													   std::make_pair<int, int>(NULL, NULL));
}

void City::generateRowNorth(int row) {

	int newYLoc = blocks[row][0]->locY + BLOCK_DIST;

	blocks[row + 1][0] = new Block(blocks[row][0]->locX,
		                           newYLoc,
								   std::make_pair<int, int>(NULL, NULL), /*top left*/
								   std::make_pair<int, int>(NULL, NULL), /*top right*/
								   blocks[row][0]->getTopLeftCoord(),    /*bottom left*/
								   blocks[row][0]->getTopRightCoord());  /*bottom right*/



	blocks[row + 1][1] = new Block(blocks[row][1]->locX,
									newYLoc,
									blocks[row + 1][0]->getTopRightCoord(),
									std::make_pair<int, int>(NULL, NULL),
									blocks[row][1]->getTopLeftCoord(),
									blocks[row][1]->getTopRightCoord());


	blocks[row + 1][2] = new Block(blocks[row][2]->locX,
									newYLoc,
									blocks[row + 1][1]->getTopRightCoord(),
									std::make_pair<int, int>(NULL, NULL),
									blocks[row][2]->getTopLeftCoord(),
									blocks[row][2]->getTopRightCoord());

	blocks[row + 1][3] = new Block(blocks[row][3]->locX,
									newYLoc,
									blocks[row + 1][2]->getTopRightCoord(),
									std::make_pair<int, int>(NULL, NULL),
									blocks[row][3]->getTopLeftCoord(),
									blocks[row][3]->getTopRightCoord());

	blocks[row + 1][4] = new Block(blocks[row][4]->locX,
									newYLoc,
									blocks[row + 1][3]->getTopRightCoord(),
									std::make_pair<int, int>(NULL, NULL),
									blocks[row][4]->getTopLeftCoord(),
									blocks[row][4]->getTopRightCoord());
}


void City::draw(DrawData& data)
{

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	
	for (int i = 0; i < CITY_LENGTH; i++) {
		for (int j = 0; j < CITY_LENGTH; j++) {

			//std::cout << "block " << j << std::endl;
			blocks[i][j]->draw(data);
		}
	}


	glPopMatrix();
}


void City::update(UpdateData& data)
{
	//
}


