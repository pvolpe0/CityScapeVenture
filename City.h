#ifndef CSE167_City_h
#define CSE167_City_h

#include "Drawable.h"
#include "Block.h"


class City : public Drawable
{

private:

	// std::pair<int, int> coords[5][5];
	Block * blocks[5][5];


public:

	City();
	virtual ~City(void);

	void generateSingleEast(int, int, std::pair<int, int>, std::pair<int, int>);

	void generateRowNorth(int);

	/*
	
	probably dont need these

	void growSingleEast(int, int, std::pair<int, int>, std::pair<int, int>);
	void growSingleNorth(std::pair<int, int>, std::pair<int, int>);
	void growSingleSouth(std::pair<int, int>, std::pair<int, int>);
	*/

	virtual void draw(DrawData&);
	virtual void update(UpdateData&);



};

#endif
