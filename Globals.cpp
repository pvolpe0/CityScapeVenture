#include "Globals.h"

Camera Globals::camera;

Cube Globals::cube(10.0);

Light Globals::light;

DrawData Globals::drawData;
UpdateData Globals::updateData;


City Globals::city;
Player Globals::player;
Skybox * Globals::skybox;


bool Globals::STREETS = 0;
bool Globals::BUILDINGS = 1;
bool Globals::TREES = 1;
bool Globals::SKYBOX = 1;
bool Globals::DEBUG = 0;