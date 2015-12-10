#ifndef CSE167_LSystemTree_h
#define CSE167_LSystemTree_h


#include "Drawable.h"
#include "Matrix4.h"
#include "Vector3.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class LSystemTree : public Drawable
{
private:
	int width, length, size;
	Vector3 currentPos, direction;
	bool flipped;
	char *str;
	float angle, anglChange;

public:
	LSystemTree(Vector3 position, Vector3 dir);//char *s, int siz);
	void draw(DrawData& data);
};

#endif
