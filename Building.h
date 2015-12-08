#ifndef CSE167_Building_h
#define CSE167_Building_h

#include "Drawable.h"

class Building : public Drawable
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
	Building(int x, int z, Matrix4 rotation, int blockGrammar);
	void draw(DrawData& data);
	void drawShape(DrawData& data);
	void drawSize(DrawData& data);
	void drawAddition(DrawData& data);
	void drawRoof(DrawData& data);
	void drawDoor(DrawData& data);
	void drawWindow(DrawData& data);
};

#endif
