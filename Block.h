#ifndef CSE167_Block_h
#define CSE167_Block_h

#include "Drawable.h"
#include <utility>
#include <tuple>

class Block : public Drawable
{

private:

	// std::pair<int, int> coords[5][5];

	std::pair<int, int> coords[2][2];
	Color lineColor;
	Color groundColor;

public:



	int locX, locY;
	Block(int, int);
	Block(int, int, std::pair<int, int>,
		            std::pair<int, int>,
					std::pair<int, int>,
					std::pair<int, int>);
	virtual ~Block(void);


	void setCoordDisplacement( std::pair<int, int>&);

	std::pair<int, int> getTopLeftCoord();
	std::pair<int, int> getTopRightCoord();
	std::pair<int, int> getBotLeftCoord();
	std::pair<int, int> getBotRightCoord();

	virtual void draw(DrawData&);
	virtual void update(UpdateData&);

	

};

#endif

