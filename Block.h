#ifndef CSE167_Block_h
#define CSE167_Block_h

#include "Drawable.h"
#include "Building.h"
#include "Vector3.h"
#include <vector>
#include <utility>
#include <tuple>

class Block : public Drawable
{

private:

	std::pair<int, int> coords[2][2];
	std::pair<float, float> sidewalk_inner_coords[2][2];
	std::pair<float, float> sidewalk_outer_coords[2][2];
	std::pair<float, float> inner_coords[2][2];

	std::pair<float, float> west_road_coords[2];
	std::pair<float, float> south_road_coords[2];
	std::pair<float, float> north_road_coords[2];
	std::pair<float, float> east_road_coords[2];

	std::vector<Building *> Buildings;

	Color platformColor;

	double northLineDist, southLineDist, westLineDist, eastLineDist;
	Vector3 westVec, northVec, eastVec, southVec;

	double getDistanceBetweenPoints(std::pair<int, int>, std::pair<int, int>);
	void setRealCoords();
	void setLineDistances();

	void generateBuildings(std::pair<float, float>, Vector3, double);

	int blockGrammar;
	int type;
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

