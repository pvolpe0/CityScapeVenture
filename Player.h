#ifndef CSE167_Player_h
#define CSE167_Player_h

#include "Drawable.h"
#include "Skybox.h"
#include "Sphere.h"
#include "Vector4.h"

class Player : public Drawable
{

public:

	int x, y;
	int prevX, prevY;

	Sphere * sphere;
	//Skybox * skybox;

	Player();
	virtual ~Player(void);

	void setDeltaLocation(int, int);

	virtual void draw(DrawData&);
	virtual void update(UpdateData&);

	Vector4 getLocation(void);


};

#endif

