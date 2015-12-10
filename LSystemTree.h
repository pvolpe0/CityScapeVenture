#ifndef CSE167_LSystemTree_h
#define CSE167_LSystemTree_h

#include "Drawable.h"
#include "Matrix4.h"
#include "Vector3.h"

class LSystemTree : public Drawable
{
private:
	int width, length, size;
	Vector3 currentPos, direction, nextPos, nextDir, secondDir, thirdDir, fourthDir;
	bool flipped;
	char *str;
	float angle, anglChange;
	Matrix4 rot;

public:
	LSystemTree();
	LSystemTree(Vector3 position, Vector3 dir, int w);//char *s, int siz);
	void draw(DrawData& data);
};

#endif
