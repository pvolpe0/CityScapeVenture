#ifndef CSE167_Player_h
#define CSE167_Player_h

#include "Drawable.h"
#include "Skybox.h"
#include "Sphere.h"
#include "Vector4.h"
#include "Vector3.h"

class Player : public Drawable
{

public:

	float x, y;
	int prevX, prevY;

	bool atIntersection;
	Vector3 northMove;
	Vector3 eastMove;
	Vector3 westMove;
	Vector3 southMove;
	Vector3 northInt;
	Vector3 southInt;
	Vector3 westInt;
	Vector3 eastInt;
	Vector3 currInt;

	Sphere * sphere;
	//Skybox * skybox;

	Player();
	virtual ~Player(void);

	void setDeltaLocation(float, float);

	virtual void draw(DrawData&);
	virtual void update(UpdateData&);

	Vector4 getLocation(void);
	void moveNorth();
	void moveSouth();
	void moveWest();
	void moveEast();


};

#endif

