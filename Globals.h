#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"
#include "Cube.h"
#include "Light.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Sphere.h"
#include "Player.h"
#include "Block.h"
#include "City.h"
#include "Skybox.h"

class Globals
{
    
public:
    
    static Camera camera;
    static Cube cube;
	static Player player;
    static Light light;
    static DrawData drawData;
    static UpdateData updateData;
    //Feel free to add more member variables as needed

	static City city;
	static Skybox * skybox;

};

#endif
