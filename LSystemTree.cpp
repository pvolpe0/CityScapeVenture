#include "LSystemTree.h"
#include <math.h>

LSystemTree::LSystemTree(Vector3 position, Vector3 dir)//, char *s, int siz)
{
	//str = s;
	//size = siz;
	currentPos = position;
	width = 5;
	length = 10;
	direction = dir;
	flipped = false;
	angle = 0;
	anglChange = .5;
}

void LSystemTree::draw(DrawData& data)
{	
	toWorld.identity();
	toWorld = Matrix4().makeTranslate(currentPos[0], currentPos[1], currentPos[2]) * toWorld;
	toWorld = Matrix4().makeRotateY(PI/2) * toWorld;
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
	//Open a polygon
	glBegin(GL_LINES);
	glVertex3f(currentPos[0], currentPos[1], currentPos[2]);
	//currentPos = currentPos + direction;
	glVertex3f( currentPos[0] + direction[0],
				currentPos[1] + direction[1],
				currentPos[2] + direction[2]);
	glEnd();
	direction = Matrix4().makeRotateX(angle) * direction;
	direction.scale(0.9);
	glLineWidth(--width);
	if(direction.magnitude() > 0 && width > 0)
	{
		LSystemTree(currentPos, direction).draw(data);
		direction = Matrix4().makeRotateY(PI) * direction;
		LSystemTree(currentPos, direction).draw(data);
	}
	//Close the polygon
	//glEnd();

}
