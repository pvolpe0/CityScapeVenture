#include "LSystemTree.h"
#include <math.h>

LSystemTree::LSystemTree(){}

LSystemTree::LSystemTree(Vector3 position, Vector3 dir, int w)//, char *s, int siz)
{
	srand(((int)position[0] << 16) + ((int)position[2]));
	currentPos = position;
	width = w;
	length = dir.magnitude();
	direction = dir;
	nextPos = currentPos + direction;

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
	glPushMatrix();
	glMultMatrixf(toWorld.ptr());
	glBegin(GL_LINES);
	glVertex3f(currentPos[0], currentPos[1], currentPos[2]);
	glVertex3f(nextPos[0],	  nextPos[1],	 nextPos[2]);
	glEnd();
	glPopMatrix();

	if(length > 2 && width > 0)
	{
		if(rand() % 10 > 2) LSystemTree(nextPos, nextDir, width-1).draw(data);
		if(rand() % 10 > 2) LSystemTree(nextPos, secondDir, width-1).draw(data);
		if(rand() % 10 > 2) LSystemTree(nextPos, thirdDir, width-1).draw(data);
		if(rand() % 10 > 2) LSystemTree(nextPos, fourthDir, width-1).draw(data);
	}
}
