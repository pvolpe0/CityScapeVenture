#ifndef CSE167_Skybox_h
#define CSE167_Skybox_h

#include "Texture.h"

class Skybox
{

public:

	Texture * back;
	Texture * base;
	Texture * front;
	Texture * left;
	Texture * right;
	Texture * top;

	Skybox();
	void draw();

};

#endif
