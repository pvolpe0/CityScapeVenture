#include "LSystemTree.h"
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

LSystemTree::LSystemTree(int x, int z, Matrix4 rotation, int blockGrammar)
{
	xLoc = x;
	zLoc = z;
	rot = rotation;
	grammar[1] = blockGrammar;
	defineGrammar(x, z);
}

void LSystemTree::defineGrammar(int x, int z)
{
	srand(x);
	int xseed = rand();
	srand(z);
	int zseed = rand();
	srand((xseed << 16) + zseed);
	rand();
	grammar[0] = rand() % 10;
	for (int i = 2;i < 6;i++)
	{
		grammar[i] = rand() % 10;
	}
}

void LSystemTree::draw(DrawData& data)
{	
	toWorld.identity();
	toWorld = Matrix4().makeTranslate(xLoc, 0, zLoc) * toWorld * rot;
	
	switch(1)
	{
		case 'F':
			//Move forward by line length drawing a line
			break;
		case 'f':
			//Move forward by line length without drawing a line
			break;
		case '+':
			//Turn left by turning angle
			break;
		case '-':
			//Turn right by turning angle
			break;
		case '|':
			//Reverse direction (ie: turn by 180 degrees)
			break;
		case '[':
			//Push current drawing state onto stack
			break;
		case ']':
			//Pop current drawing state from the stack
			break;
		case '#':
			//Increment the line width by line width increment
			break;
		case '!':
			//Decrement the line width by line width increment
			break;
		case '@':
			//Draw a dot with line width radius
			break;
		case '{':
			//Open a polygon
			break;
		case '}':
			//Close a polygon and fill it with fill colour
			break;
		case '>':
			//Multiply the line length by the line length scale factor
			break;
		case '<':
			//Divide the line length by the line length scale factor
			break;
		case '&':
			//Swap the meaning of + and -
			break;
		case '(':
			//Decrement turning angle by turning angle increment
			break;
		case ')':
			//Increment turning angle by turning angle increment
			break;
		default:;
	}
}

void LSystemTree::drawSize(DrawData & data)
{
	switch (grammar[1] % 5)
	{
	case 0:
		size = Matrix4().makeScale(10);
		front = 10;
		break;
	case 1:
		size = Matrix4().makeScale(12, 30, 12);
		front = 12;
		break;
	case 2:
		size = Matrix4().makeScale(15, 10, 10);
		front = 10;
		break;
	case 3:
		size = Matrix4().makeScale(10, 15, 15);
		front = 15;
		break;
	case 4:
		size = Matrix4().makeScale(15, 8, 15);
		front = 15;
		break;
	}
}

