#ifndef CSE167_LSystemTree_h
#define CSE167_LSystemTree_h


#include "Drawable.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Cylinder.h"
#include "Sphere.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class LSystemTree : public Drawable
{
private:
	float width, length;
	Vector3 currentPos, direction, nextPos, nextDir,
			secondDir, thirdDir, fourthDir;
	Drawable *model;
	Cylinder cyl;
	Sphere sph;
	Matrix4 rot1, rot2, rot3, rot4;
	float angle;
	Matrix4 rotate;

public:
	LSystemTree();
	LSystemTree(Vector3 position, Vector3 dir, Matrix4 r, float w);
	void draw(DrawData& data);
};

#endif
