#ifndef CSE167_Block_h
#define CSE167_Block_h

#include "Drawable.h"
#include <utility>
#include <tuple>

class Block : public Drawable
{

private:

	std::pair<int, int> coords[5][5];


public:

	int locX, locY;
	Block(int, int);
	virtual ~Block(void);

	void setCoordDisplacement();

	virtual void draw(DrawData&);
	virtual void update(UpdateData&);

	

};

#endif

