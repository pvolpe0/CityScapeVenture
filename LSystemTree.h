#ifndef CSE167_LSystemTree_h
#define CSE167_LSystemTree_h

#include "Drawable.h"

class LSystemTree : public Drawable
{
private:
	int xLoc;
	int zLoc;
	Matrix4 rot;
	int grammar[6];
	void defineGrammar(int x, int z);
	Matrix4 size;
	int front;

public:
	LSystemTree(int x, int z, Matrix4 rotation, int blockGrammar);
	void draw(DrawData& data);
	void drawShape(DrawData& data);
	void drawSize(DrawData& data);
	void drawAddition(DrawData& data);
	void drawRoof(DrawData& data);
	void drawDoor(DrawData& data);
	void drawWindow(DrawData& data);
};

#endif
