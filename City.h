#ifndef CSE167_City_h
#define CSE167_City_h

#include "Drawable.h"
#include "Block.h"


class City : public Drawable
{

private:

	std::pair<int, int> coords[5][5];
	Block * blocks[5][5];


public:

	City();
	virtual ~City(void);

	virtual void draw(DrawData&);
	virtual void update(UpdateData&);



};

#endif
