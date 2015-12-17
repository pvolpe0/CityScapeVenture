#include "City.h"
#include "Globals.h"
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define CITY_LENGTH 5
#define BLOCK_DIST 400

City::City() : Drawable()
{
	// create starting block
	blocks[0][0] = new Block(-800, -800);

	
	// generate first row of blocks
	for (int i = 0; i < CITY_LENGTH; i++) {
		generateSingleEast(0, i, blocks[0][i]->getTopRightCoord(), blocks[0][i]->getBotRightCoord());
	}
	
	
	// generate rows
	generateRowNorth(0);
	generateRowNorth(1);
	generateRowNorth(2);
	generateRowNorth(3);
	

}


City::~City() {}

void City::generateSingleEast(int row, int col, std::pair<int, int> topCoord, std::pair<int, int> botCoord){

	int newXLoc = blocks[row][col]->locX + (BLOCK_DIST - 1 * !Globals::STREETS);
	int newYLoc = blocks[row][col]->locY;

	blocks[row][col + 1] = new Block(newXLoc, newYLoc, topCoord,
													   std::make_pair<int, int>(NULL, NULL),
													   botCoord,
													   std::make_pair<int, int>(NULL, NULL));
}

// used for city construction
void City::generateRowNorth(int row) {

	int newYLoc = blocks[row][0]->locY + (BLOCK_DIST - 1 * !Globals::STREETS);

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

// used dynamically
void City::generateRowNorth() {

	Block * one = blocks[0][0];
	Block * two = blocks[0][1];
	Block * three = blocks[0][2];
	Block * four = blocks[0][3];
	Block * five = blocks[0][4];


	/* remove blocks */
	for (int i = 0; i < CITY_LENGTH; i++) {

		blocks[0][i] = blocks[1][i];
		blocks[1][i] = blocks[2][i];
		blocks[2][i] = blocks[3][i];
		blocks[3][i] = blocks[4][i];

	}

	delete one;
	delete two;
	delete three;
	delete four;
	delete five;

	int newYLoc = blocks[3][0]->locY + (BLOCK_DIST - 1 * !Globals::STREETS);

	
	blocks[4][0] = new Block(blocks[3][0]->locX,
		newYLoc,
		std::make_pair<int, int>(NULL, NULL), /*top left*/
		std::make_pair<int, int>(NULL, NULL), /*top right*/
		blocks[3][0]->getTopLeftCoord(),    /*bottom left*/
		blocks[3][0]->getTopRightCoord());  /*bottom right*/


	for (int i = 0; i < CITY_LENGTH - 1; i++) {
		
		blocks[4][i + 1] = new Block(blocks[3][i + 1]->locX,
			newYLoc,
			blocks[4][i]->getTopRightCoord(),
			std::make_pair<int, int>(NULL, NULL),
			blocks[3][i + 1]->getTopLeftCoord(),
			blocks[3][i + 1]->getTopRightCoord());
	}


}

void City::generateRowSouth() {

	Block * one = blocks[4][0];
	Block * two = blocks[4][1];
	Block * three = blocks[4][2];
	Block * four = blocks[4][3];
	Block * five = blocks[4][4];


	/* remove blocks */
	for (int i = 0; i < CITY_LENGTH; i++) {

		blocks[4][i] = blocks[3][i];
		blocks[3][i] = blocks[2][i];
		blocks[2][i] = blocks[1][i];
		blocks[1][i] = blocks[0][i];

	}

	delete one;
	delete two;
	delete three;
	delete four;
	delete five;

	int newYLoc = blocks[1][0]->locY - (BLOCK_DIST - 1 * !Globals::STREETS);


	blocks[0][0] = new Block(blocks[1][0]->locX,
		newYLoc,
		blocks[1][0]->getBotLeftCoord(),		//top left
		blocks[1][0]->getBotRightCoord(),		//top right
		std::make_pair<int, int>(NULL, NULL),   //bottom left
		std::make_pair<int, int>(NULL, NULL));  //bottom right

		
	for (int i = 0; i < CITY_LENGTH - 1; i++) {

		blocks[0][i + 1] = new Block(blocks[1][i + 1]->locX,
			newYLoc,
		
			blocks[0][i]->getTopRightCoord(),
			blocks[1][i + 1]->getBotRightCoord(),	
			blocks[0][i]->getBotRightCoord(),
			std::make_pair<int, int>(NULL, NULL));
	}

}

void City::generateRowEast() {

	Block * one = blocks[4][4];
	Block * two = blocks[3][4];
	Block * three = blocks[2][4];
	Block * four = blocks[1][4];
	Block * five = blocks[0][4];


	/* remove blocks */
	for (int i = 0; i < CITY_LENGTH; i++) {

		blocks[i][4] = blocks[i][3];
		blocks[i][3] = blocks[i][2];
		blocks[i][2] = blocks[i][1];
		blocks[i][1] = blocks[i][0];


	}


	delete one;
	delete two;
	delete three;
	delete four;
	delete five;

	int newXLoc = blocks[1][0]->locX - (BLOCK_DIST - 1 * !Globals::STREETS);


	blocks[0][0] = new Block(newXLoc,
		blocks[0][1]->locY,
		std::make_pair<int, int>(NULL, NULL),		//top left
		blocks[0][1]->getTopLeftCoord(),		//top right
		std::make_pair<int, int>(NULL, NULL),   //bottom left
		blocks[0][1]->getBotLeftCoord());  //bottom right


	for (int i = 0; i < CITY_LENGTH - 1; i++) {

		blocks[i + 1][0] = new Block(newXLoc,
			blocks[i + 1][1]->locY,

			std::make_pair<int, int>(NULL, NULL),
			blocks[i + 1][1]->getTopLeftCoord(),
			blocks[i][0]->getTopLeftCoord(),
			blocks[i + 1][1]->getBotLeftCoord() );
	}
	
}


void City::generateRowWest() {

	Block * one = blocks[4][0];
	Block * two = blocks[3][0];
	Block * three = blocks[2][0];
	Block * four = blocks[1][0];
	Block * five = blocks[0][0];


	/* remove blocks */
	for (int i = 0; i < CITY_LENGTH; i++) {

		blocks[i][0] = blocks[i][1];
		blocks[i][1] = blocks[i][2];
		blocks[i][2] = blocks[i][3];
		blocks[i][3] = blocks[i][4];
		
		
		


	}


	delete one;
	delete two;
	delete three;
	delete four;
	delete five;

	int newXLoc = blocks[0][3]->locX + (BLOCK_DIST - 1 * !Globals::STREETS);


	blocks[0][4] = new Block(newXLoc,
		blocks[0][3]->locY,
		blocks[0][3]->getTopRightCoord(),		//top left
		std::make_pair<int, int>(NULL, NULL),		//top right
		blocks[0][3]->getBotRightCoord(),   //bottom left
		std::make_pair<int, int>(NULL, NULL));  //bottom right


	for (int i = 0; i < CITY_LENGTH - 1; i++) {

		blocks[i + 1][4] = new Block(newXLoc,
			blocks[i + 1][3]->locY,

			blocks[i + 1][3]->getTopRightCoord(),
			std::make_pair<int, int>(NULL, NULL),

			blocks[i + 1][3]->getBotRightCoord(),
			blocks[i][4]->getTopRightCoord());
	}
	
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

std::pair<int, int> City::getMiddle()
{
	return blocks[2][2]->getBotLeftCoord();
}


