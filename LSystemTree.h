#ifndef CSE167_LSystemTree_h
#define CSE167_LSystemTree_h


#include "Drawable.h"
#include "Matrix4.h"
#include "Vector3.h"

#ifdef __APPLE__
<<<<<<< HEAD
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
=======
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
>>>>>>> 683fb8ff0292346d4d451c017891821ca3f566bd
#endif

class LSystemTree : public Drawable
{
private:
	int width, length;
	Vector3 currentPos, direction, nextPos, nextDir,
			secondDir, thirdDir, fourthDir;
	float angle;
	Matrix4 rot;

public:
	LSystemTree();
	LSystemTree(Vector3 position, Vector3 dir, int w);
	void draw(DrawData& data);
};

#endif
