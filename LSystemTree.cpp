#include "LSystemTree.h"
#include <math.h>

LSystemTree::LSystemTree(){}

LSystemTree::LSystemTree(Vector3 position, Vector3 dir, Matrix4 r, float w)//, char *s, int siz)
{
	srand(((int)position[0] << 16) + ((int)position[2]));
	currentPos = position;
	width = w;
	length = dir.magnitude();
	direction = dir;
	nextPos = currentPos + direction;

	glLineWidth(width);
	
	angle = (rand() % 10)/8.f;
	rot1 = Matrix4().makeRotateX(angle);
	nextDir = (rot1 * direction);//.scale(0.7);
	
	cyl = Cylinder(width, length, 6, 6);
	sph = Sphere(2, 5, 5);

	angle = (rand() % 10)/8.f;
	rot2 = Matrix4().makeRotateZ(angle);
	secondDir = (rot2 * direction);//.scale(0.7);

	angle = (rand() % 10)/8.f;
	rot3 = Matrix4().makeRotateX(-angle);
	thirdDir = (rot3 * direction);//.scale(0.7);
	
	angle = (rand() % 10)/8.f;
	rot4 = Matrix4().makeRotateZ(-angle);
	fourthDir = (rot4 * direction);//.scale(0.7);

	rotate = r;
}

void LSystemTree::draw(DrawData& data)
{
	glPushMatrix();
	glMultMatrixf((Matrix4().makeTranslate(currentPos) *
				   rotate *
				   Matrix4().makeRotateX(-PI/2)).ptr());
	
	//cyl.draw(data);

	if(width < 0.7) sph.draw(data);
	else cyl.draw(data);

	glPopMatrix();

	if(length > 2 && width > 0.7)
	{
		//if(rand() % 10 > 2)
			LSystemTree(nextPos, nextDir, rot1 * rotate, width-0.2).draw(data);
		//if(rand() % 10 > 2)
			LSystemTree(nextPos, secondDir, rot2 * rotate, width-0.2).draw(data);
		//if(rand() % 10 > 2)
			LSystemTree(nextPos, thirdDir, rot3 * rotate, width-0.2).draw(data);
		//if(rand() % 10 > 2)
			LSystemTree(nextPos, fourthDir, rot4 * rotate, width-0.2).draw(data);
	}
}
