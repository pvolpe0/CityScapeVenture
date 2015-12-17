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
    static Light light;
    static DrawData drawData;
    static UpdateData updateData;
    //Feel free to add more member variables as needed

	static City city;
	static Player player;
	static Skybox * skybox;

	static bool BUILDINGS;
	static bool STREETS;
	static bool TREES;
	static bool SKYBOX;
	static bool DEBUG;
		
};

#endif
