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
#include "Block.h"
#include "Building.h"

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here
int mouseButton;
int mouseX;
int mouseY;


void Window::initialize(void)
{

	std::pair<int, int> init = Globals::city.getMiddle();
	Globals::player.setDeltaLocation(init.first, init.second);
	Globals::camera.move(Vector3(init.first, 0, init.second));

	Globals::skybox = new Skybox(Matrix4().makeTranslate(init.first, 0, init.second));
	Globals::skybox->back = new Texture("hills_bk.ppm");
	Globals::skybox->base = new Texture("hills_dn.ppm");
	Globals::skybox->front = new Texture("hills_ft.ppm");
	Globals::skybox->left = new Texture("hills_rt.ppm");
	Globals::skybox->right = new Texture("hills_lf.ppm");
	Globals::skybox->top = new Texture("hills_up.ppm");

    //Setup the light
	Vector4 lightPos = Vector4(0.0, -3.0, 0.0, 0) + Globals::camera.getDirection();
    Globals::light.position = lightPos;
    Globals::light.quadraticAttenuation = 0.000;
    
    //Initialize cube matrix:

    //Setup the cube's material properties
    Color color(0x23ff27ff);
    Globals::cube.material.color = color;

}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
    
    //Rotate cube; if it spins too fast try smaller values and vice versa
    Globals::cube.spin(0.0005);
    
    //Call the update function on cube
    Globals::cube.update(Globals::updateData);

    
    //Call the display routine to draw the cube
    displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1700.0); //Set perspective projection viewing frustum
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set the OpenGL matrix mode to ModelView
    glMatrixMode(GL_MODELVIEW);
    
    //Push a matrix save point
    //This will save a copy of the current matrix so that we can
    //make changes to it and 'pop' those changes off later.
    glPushMatrix();
    
    //Replace the current top of the matrix stack with the inverse camera matrix
    //This will convert all world coordiantes into camera coordiantes
    glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());
    
    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)
    Globals::light.bind(0);
    
    //Draw the cube!
    //Globals::cube.draw(Globals::drawData);
	Globals::player.draw(Globals::drawData);
	Globals::skybox->draw();
	//Globals::player.draw(Globals::drawData);
	
	//Globals::block.draw(Globals::drawData);
	Globals::city.draw(Globals::drawData);

	//glPushMatrix();
	//glMultMatrixf(Matrix4().makeTranslate(Globals::light.position[0], Globals::light.position[1], Globals::light.position[2]).ptr());
	//glutSolidSphere(20, 20, 20);
	//glPopMatrix();
	
	/*srand(500);
	for (int i = -250;i < 250;i += 40)
	{
		for (int j = -250;j < 250;j += 40)
		{

			Building(i, j, Matrix4().makeRotateY(0), rand() % 10).draw(Globals::drawData);
		}
	}*/
	
	//std::cout << "Player Location | (x,y) : (" << Globals::player.x << "," << Globals::player.y << ")" << std::endl;

	//std::cout << "Player location: (" << Globals::player.x << ","
	//	<< Globals::player.y << ")" << std::endl;
    
    //Pop off the changes we made to the matrix stack this frame
    glPopMatrix();
    
    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    glFlush();
    
    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
}

void Window::keyboard(unsigned char key, int x, int y)
{
	//Commented out is for first person camera
	/*switch (key)
	{
	case 'w':
		Globals::camera.move(Vector3(0, 0, -5));
		break;
	case 'a':
		Globals::camera.move(Vector3(-5, 0, 0));
		break;
	case 's':
		Globals::camera.move(Vector3(0, 0, 5));
		break;
	case 'd':
		Globals::camera.move(Vector3(5, 0, 0));
		break;
	}*/
	//Below code is for debug camera
	switch(key)
	{
	case 27: //ESC
		exit(0);
		break;
	/*case 'w':
		Globals::camera.transform(Matrix4().makeTranslate(0, 0, -5));
		break;
	case 'a':
		Globals::camera.transform(Matrix4().makeTranslate(-5, 0, 0));
		break;
	case 's':
		Globals::camera.transform(Matrix4().makeTranslate(0, 0, 5));
		break;
	case 'd':
		Globals::camera.transform(Matrix4().makeTranslate(5, 0, 0));
		break;*/
	case 'w':

		Globals::player.toWorld = Globals::player.toWorld * Matrix4().makeTranslate(0, 0, 5);
		Globals::player.setDeltaLocation(0, 5);
		Globals::camera.move(Vector3(0, 0, 5));
		Globals::skybox->toWorld = Globals::skybox->toWorld * Matrix4().makeTranslate(0, 0, 5);
		if (abs(155 - Globals::player.y) % 300 == 0)
			Globals::city.generateRowNorth(); 
		break;
	case 'a':
		Globals::player.toWorld = Globals::player.toWorld * Matrix4().makeTranslate(5, 0, 0);
		Globals::player.setDeltaLocation(5, 0);
		Globals::camera.move(Vector3(5, 0, 0));
		Globals::skybox->toWorld = Globals::skybox->toWorld * Matrix4().makeTranslate(5, 0, 0);
		if (abs(155 - Globals::player.x) % 300 == 0)
			Globals::city.generateRowWest();
		break;
	case 's':
		Globals::player.toWorld = Globals::player.toWorld * Matrix4().makeTranslate(0, 0, -5);
		Globals::player.setDeltaLocation(0, -5);
		Globals::camera.move(Vector3(0, 0, -5));
		Globals::skybox->toWorld = Globals::skybox->toWorld * Matrix4().makeTranslate(0, 0, -5);
		if (abs(Globals::player.y) % 300 == 150)
			Globals::city.generateRowSouth();
		break;
	case 'd':
		Globals::player.toWorld = Globals::player.toWorld * Matrix4().makeTranslate(-5, 0, 0);
		Globals::player.setDeltaLocation(-5, 0);
		Globals::camera.move(Vector3(-5, 0, 0));
		Globals::skybox->toWorld = Globals::skybox->toWorld * Matrix4().makeTranslate(-5, 0, 0);
		if (abs(Globals::player.x) % 300 == 150)
			Globals::city.generateRowEast();
		break;
	}
	//Vector4 lightPos = Globals::player.getLocation() + Vector4(0, 20, 0, 0);
	//Globals::light.position = lightPos;
	std::cout << Globals::player.getLocation()[0] << " " << Globals::player.getLocation()[2] << std::endl;
}

void Window::onMouseClick(int button, int state, int x, int y)
{
	mouseButton = button;
	mouseX = x;
	mouseY = y;
}

void Window::onMouseMove(int x, int y)
{
	float movedx = x - mouseX;
	float movedy = y - mouseY;
	mouseX = x;
	mouseY = y;
	
	Globals::camera.rotate(Matrix4().makeRotateY(-movedx / 150));
	Globals::camera.look(-movedy / 150.0);
	Vector4 lightPos = Vector4(0.0, -3.0, 0.0, 0) + Globals::camera.getDirection();
	Globals::light.position = lightPos;
	

	//Globals::camera.transform(Matrix4().makeRotateY(-movedx / 50) * Matrix4().makeRotateX(-movedy / 50));
}

//TODO: Keyboard callbacks!

//TODO: Function Key callbacks!

//TODO: Mouse callbacks!

//TODO: Mouse Motion callbacks!
