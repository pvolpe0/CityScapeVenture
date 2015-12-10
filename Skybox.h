#ifndef CSE167_Skybox_h
#define CSE167_Skybox_h

#include "Texture.h"
#include "Drawable.h"

class Skybox: public Drawable
{

public:

	Texture * back;
	Texture * base;
	Texture * front;
	Texture * left;
	Texture * right;
	Texture * top;

	Skybox(Matrix4 init);
	void draw();

};

#endif
