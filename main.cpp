#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "Globals.h"

void runIntro() {

	bool finished;

	std::cout << "Welcome to CityScape Venture, before we jump in, lets enter some preferences.\n\n" << std::endl;

	std::cout << "Enter 1 to begin the finished product, Enter 0 for custom options." << std::endl;
	std::cin >> finished;

	if (!finished) {

		std::cout << "You chose custom options\n" << std::endl;
		std::cout << "Generate buildings?" << std::endl;
		std::cout << "Enter 1 for yes, enter 0 for no" << std::endl;

		std::cin >> Globals::BUILDINGS;

		std::cout << "Generate trees?" << std::endl;
		std::cout << "Note: Having this off will greatly improve performance" << std::endl;

		std::cout << "Enter 1 for yes, enter 0 for no" << std::endl;

		std::cin >> Globals::TREES;

		if (!Globals::BUILDINGS && !Globals::TREES) {

			std::cout << "Street randomness" << std::endl;
			std::cout << "Enter 1 for standard grid-like, enter 0 for random streets" << std::endl;

			std::cin >> Globals::STREETS;

			Globals::STREETS = !Globals::STREETS;
		}

		std::cout << "Render Block debug lines?" << std::endl;
		std::cout << "Enter 1 for yes, enter 0 for no" << std::endl;

		std::cin >> Globals::DEBUG;

		if (Globals::DEBUG) {

			std::cout << "\n\nYou've seleceted debug lines on" << std::endl;
			std::cout << "\nFive sets of lines will be shown" << std::endl;

			std::cout << "\t1. Purple - Geographic center of a block, RNG seed value for the block is based on these x,y values" << std::endl;
			std::cout << "\t2. Blue - Corners of block objects" << std::endl;
			std::cout << "\t3. Light Blue - Sidewalk outer corners" << std::endl;
			std::cout << "\t4. Green - Sidewalk inner corners" << std::endl;
			std::cout << "\t5. Yellow - Buidling generation starting location\n" << std::endl;




		}
	}
}

int main(int argc, char *argv[])
{



	runIntro();

    //GLUT and OpenGL Configuration
    glutInit(&argc, argv);                                      //Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   //Open an OpenGL context with double buffering, RGB colors, and depth buffering
    glutInitWindowSize(Window::width, Window::height);          //Set initial window size
    glutCreateWindow("UCSD CSE 167 Final Project - CityScapeVenture"); //Open window and set window title
    
    glEnable(GL_DEPTH_TEST);                                    //Enable depth buffering
    glClear(GL_DEPTH_BUFFER_BIT);                               //Clear depth buffer
    glClearColor(0.0, 0.0, 0.0, 0.0);                           //Set clear color to black
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);                  //Set polygon drawing mode to fill front and back of each polygon
    glDisable(GL_CULL_FACE);                                    //Disable backface culling to render both sides of polygons
    glShadeModel(GL_SMOOTH);                                    //Set shading to smooth
    
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);                                //Enable color materials
    glEnable(GL_LIGHTING);                                      //Enable lighting
    glEnable(GL_NORMALIZE);                                     //Auto normalize surface normals
    glEnable(GL_TEXTURE_2D);                                    //Enable 2D textures
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);        //Enable Local Viewer Light Model
    
    //Register callback functions:
    glutDisplayFunc(Window::displayCallback);
    glutReshapeFunc(Window::reshapeCallback);
    glutIdleFunc(Window::idleCallback);
	glutMouseFunc(Window::onMouseClick);
	glutKeyboardFunc(Window::keyboard);
	glutMotionFunc(Window::onMouseMove);
    
    //Print Shader Debug Information:
    printf("%s\n%s\n",
           glGetString(GL_RENDERER),  // e.g. Intel HD Graphics 3000 OpenGL Engine
           glGetString(GL_VERSION)    // e.g. 3.2 INTEL-8.0.61
           );
    
    //If the shading language symbol is defined
    #ifdef GL_SHADING_LANGUAGE_VERSION
    std::printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
    #endif
    
    //Initialize the Window:
    //The body of this function is a great place to load textures, shaders, etc.
    //and do any operations/calculations/configurations that only need to happen once.
    Window::initialize();
    
    //Start up the render loop!
    glutMainLoop();
    
    return 0;
}

