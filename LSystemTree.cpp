#include "LSystemTree.h"
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

LSystemTree::LSystemTree(){}

LSystemTree::LSystemTree(Vector3 position, Vector3 dir, int w)//, char *s, int siz)
{
	//str = s;
	//size = siz;
	srand(((int)position[0] << 16) + ((int)position[2]));
	currentPos = position;
	width = w;
	length = dir.magnitude();
	direction = dir;
	nextPos = currentPos + direction;
	flipped = false;
	
	glLineWidth(width);
	
	angle = (rand() % 10)/8.f;
	rot = Matrix4().makeRotateX(angle);
	nextDir = (rot * direction).scale(0.7);
	
	angle = (rand() % 10)/8.f;
	rot = Matrix4().makeRotateZ(angle);
	secondDir = (rot * direction).scale(0.7);

	angle = (rand() % 10)/8.f;
	rot = Matrix4().makeRotateX(-angle);
	thirdDir = (rot * direction).scale(0.7);
	
	angle = (rand() % 10)/8.f;
	rot = Matrix4().makeRotateZ(-angle);
	fourthDir = (rot * direction).scale(0.7);
}

void LSystemTree::draw(DrawData& data)
{
	//toWorld = toWorld * Matrix4().makeRotateY(PI/2);
/*
	for(int i = 0; i < size; i++)
	{
		switch(str[i])
		{
			case 'F':
				//Move forward by length drawing a line
				glVertex3f(currentPos[0], currentPos[1], currentPos[2]);
				currentPos = currentPos + direction;
				glVertex3f(currentPos[0], currentPos[1], currentPos[2]);
				break;
			case 'f':
				//Move forward by length without drawing a cylinder
				currentPos = currentPos + direction;
				break;
			case '+':
				//Turn left by turning angle
				direction = Matrix4().makeRotateX((flipped) ? -angle : angle) * direction;
				break;
			case '-':
				//Turn right by turning angle
				direction = Matrix4().makeRotateX((flipped) ? angle : -angle) * direction;
				break;
			case '|':
				//Reverse direction (ie: turn by 180 degrees)
				direction = Matrix4().makeRotateX(PI) * direction;
				break;
			case '[':
				//Push current drawing state onto stack
					//?
				break;
			case ']':
				//Pop current drawing state from the stack
					//?
				break;
			case '#':
				//Thicken Line
				glLineWidth(++width);
				break;
			case '!':
				//Thin line
				glLineWidth(--width);
				break;
			case '{':
				//Open a polygon
				glBegin(GL_LINES);
				break;
			case '}':
				//Close a polygon and fill it with fill colour
				glEnd();
				break;
			case '>':
				//Increase Length
				length += 2;
				break;
			case '<':
				//Decrease Length
				length -= 2;
				break;
			case '&':
				//Swap the meaning of + and -
				flipped = !flipped;
				break;
			case '(':
				//Decrement turning angle by turning angle increment
				angle -= anglChange;
				break;
			case ')':
				//Increment turning angle by turning angle increment
				angle += anglChange;
				break;
			default:;
		}
	}
*/
	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	//Open a polygon
	glBegin(GL_LINES);
	glVertex3f(currentPos[0], currentPos[1], currentPos[2]);
	glVertex3f(nextPos[0],	  nextPos[1],	 nextPos[2]);
	//glVertex3f( currentPos[0] + direction[0],
	//			currentPos[1] + direction[1],
	//			currentPos[2] + direction[2]);
	glEnd();
	glPopMatrix();

	if(direction.magnitude() > 2)// && width > 0)
	{
		//std::cout << "Length:\t" << direction.magnitude() << std::endl;
		//std::cout << "Width:\t" << width << std::endl;
		if(rand() % 10 > 2) LSystemTree(nextPos, nextDir, width-1).draw(data);
		if(rand() % 10 > 2) LSystemTree(nextPos, secondDir, width-1).draw(data);
		if(rand() % 10 > 2) LSystemTree(nextPos, thirdDir, width-1).draw(data);
		if(rand() % 10 > 2) LSystemTree(nextPos, fourthDir, width-1).draw(data);
	}
	//Close the polygon
	//glEnd();

}
