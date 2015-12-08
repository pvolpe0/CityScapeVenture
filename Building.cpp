#include "Building.h"
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

float pi = 3.14159263538979323846;

Building::Building(int x, int z, Matrix4 rotation, int blockGrammar)
{
	xLoc = x;
	zLoc = z;
	rot = rotation;
	grammar[1] = blockGrammar;
	defineGrammar(x, z);
}

void Building::defineGrammar(int x, int z)
{
	srand(x);
	int xseed = rand();
	srand(z);
	int zseed = rand();
	srand((xseed << 16) + zseed);
	rand();
	grammar[0] = rand() % 10;
	for (int i = 2;i < 6;i++)
	{
		grammar[i] = rand() % 10;
	}
}

void Building::draw(DrawData& data)
{	
	toWorld.identity();
	toWorld = Matrix4().makeTranslate(xLoc, 0, zLoc) * toWorld * rot;
	drawSize(data);
	drawShape(data);
	//drawAddition(data);
	drawRoof(data);
	drawDoor(data);
	drawWindow(data);

}

void Building::drawShape(DrawData & data)
{
	material.apply();

	//Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
	glMatrixMode(GL_MODELVIEW);

	//Push a save state onto the matrix stack, and multiply in the toWorld matrix
	glPushMatrix();
	glMultMatrixf((toWorld * size).ptr());

	switch (grammar[0] % 4)
	{
	case 0:
		glBegin(GL_QUADS);

		// Draw front face:
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-1, 2, 1);
		glVertex3f(1, 2, 1);
		glVertex3f(1, 0, 1);
		glVertex3f(-1, 0, 1);

		// Draw left side:
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(-1, 2, 1);
		glVertex3f(-1, 2, -1);
		glVertex3f(-1, 0, -1);
		glVertex3f(-1, 0, 1);

		// Draw right side:
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(1, 2, 1);
		glVertex3f(1, 2, -1);
		glVertex3f(1, 0, -1);
		glVertex3f(1, 0, 1);

		// Draw back face:
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(-1, 2, -1);
		glVertex3f(1, 2, -1);
		glVertex3f(1, 0, -1);
		glVertex3f(-1, 0, -1);

		// Draw top side:
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-1, 2, 1);
		glVertex3f(1, 2, 1);
		glVertex3f(1, 2, -1);
		glVertex3f(-1, 2, -1);

		// Draw bottom side:
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(-1, 0, -1);
		glVertex3f(1, 0, -1);
		glVertex3f(1, 0, 1);
		glVertex3f(-1, 0, 1);

		glEnd();
		break;

	case 1:
		glBegin(GL_QUADS);

		// Draw front face:
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-0.5, 2, 1);
		glVertex3f(0.5, 2, 1);
		glVertex3f(0.5, 0, 1);
		glVertex3f(-0.5, 0, 1);

		glNormal3f(-1.0, 0.0, 1.0);
		glVertex3f(-1, 2, 0.5);
		glVertex3f(-0.5, 2, 1);
		glVertex3f(-0.5, 0, 1);
		glVertex3f(-1, 0, 0.5);

		glNormal3f(1.0, 0.0, 1.0);
		glVertex3f(0.5, 2, 1);
		glVertex3f(1, 2, 0.5);
		glVertex3f(1, 0, 0.5);
		glVertex3f(0.5, 0, 1);

		// Draw left side:
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(-1, 2, -1);
		glVertex3f(-1, 2, 0.5);
		glVertex3f(-1, 0, 0.5);
		glVertex3f(-1, 0, -1);

		// Draw right side:
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(1, 2, -1);
		glVertex3f(1, 2, 0.5);
		glVertex3f(1, 0, 0.5);
		glVertex3f(1, 0, -1);

		// Draw back face:
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(-1, 2, -1);
		glVertex3f(1, 2, -1);
		glVertex3f(1, 0, -1);
		glVertex3f(-1, 0, -1);

		// Draw top side:
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-1, 2, -1);
		glVertex3f(1, 2, -1);
		glVertex3f(1, 2, 0.5);
		glVertex3f(-1, 2, 0.5);

		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-1, 2, 0.5);
		glVertex3f(1, 2, 0.5);
		glVertex3f(0.5, 2, 1);
		glVertex3f(-0.5, 2, 1);

		// Draw bottom side:
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(-1, 0, -1);
		glVertex3f(1, 0, -1);
		glVertex3f(1, 0, 0.5);
		glVertex3f(-1, 0, 0.5);

		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-1, 0, 0.5);
		glVertex3f(1, 0, 0.5);
		glVertex3f(0.5, 0, 1);
		glVertex3f(-0.5, 0, 1);

		glEnd();
		break;
	case 2:

		glBegin(GL_QUADS);
		// Draw front face:
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-tan(2 * pi / 12), 2, 1);
		glVertex3f(tan(2 * pi / 12), 2, 1);
		glVertex3f(tan(2 * pi / 12), 0, 1);
		glVertex3f(-tan(2 * pi / 12), 0, 1);

		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(-tan(2 * pi / 12), 2, -1);
		glVertex3f(tan(2 * pi / 12), 2, -1);
		glVertex3f(tan(2 * pi / 12), 0, -1);
		glVertex3f(-tan(2 * pi / 12), 0, -1);

		glNormal3f(-cos(2 * pi / 12), 0.0, sin(2 * pi / 12));
		glVertex3f(-1 / cos(2 * pi / 12), 2, 0);
		glVertex3f(-tan(2 * pi / 12), 2, 1);
		glVertex3f(-tan(2 * pi / 12), 0, 1);
		glVertex3f(-1 / cos(2 * pi / 12), 0, 0);

		glNormal3f(cos(2 * pi / 12), 0.0, sin(2 * pi / 12));
		glVertex3f(tan(2 * pi / 12), 2, 1);
		glVertex3f(1 / cos(2 * pi / 12), 2, 0);
		glVertex3f(1 / cos(2 * pi / 12), 0, 0);
		glVertex3f(tan(2 * pi / 12), 0, 1);

		glNormal3f(-cos(2 * pi / 12), 0.0, -sin(2 * pi / 12));
		glVertex3f(-1 / cos(2 * pi / 12), 2, 0);
		glVertex3f(-tan(2 * pi / 12), 2, -1);
		glVertex3f(-tan(2 * pi / 12), 0, -1);
		glVertex3f(-1 / cos(2 * pi / 12), 0, 0);

		glNormal3f(cos(2 * pi / 12), 0.0, -sin(2 * pi / 12));
		glVertex3f(tan(2 * pi / 12), 2, -1);
		glVertex3f(1 / cos(2 * pi / 12), 2, 0);
		glVertex3f(1 / cos(2 * pi / 12), 0, 0);
		glVertex3f(tan(2 * pi / 12), 0, -1);

		glEnd();

		glBegin(GL_POLYGON);
		glNormal3f(0, 2, 0);
		glVertex3f(-tan(2 * pi / 12), 2, -1);
		glVertex3f(tan(2 * pi / 12), 2, -1);
		glVertex3f(1 / cos(2 * pi / 12), 2, 0);
		glVertex3f(tan(2 * pi / 12), 2, 1);
		glVertex3f(-tan(2 * pi / 12), 2, 1);
		glVertex3f(-1 / cos(2 * pi / 12), 2, 0);

		glEnd();

		glBegin(GL_POLYGON);
		glNormal3f(0, 0, 0);
		glVertex3f(-tan(2 * pi / 12), 0, -1);
		glVertex3f(tan(2 * pi / 12), 0, -1);
		glVertex3f(1 / cos(2 * pi / 12), 0, 0);
		glVertex3f(tan(2 * pi / 12), 0, 1);
		glVertex3f(-tan(2 * pi / 12), 0, 1);
		glVertex3f(-1 / cos(2 * pi / 12), 0, 0);

		glEnd();
		break;

	case 3:
		glBegin(GL_QUADS);

		// Draw front face:
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-0.5, 2, 1);
		glVertex3f(0.5, 2, 1);
		glVertex3f(0.5, 0, 1);
		glVertex3f(-0.5, 0, 1);

		// Draw left side:
		glNormal3f(-1.0, 0.0, 1.0);
		glVertex3f(-1, 2, -1);
		glVertex3f(-0.5, 2, 1);
		glVertex3f(-0.5, 0, 1);
		glVertex3f(-1, 0, -1);

		// Draw right side:
		glNormal3f(1.0, 0.0, 1.0);
		glVertex3f(0.5, 2, 1);
		glVertex3f(1, 2, -1);
		glVertex3f(1, 0, -1);
		glVertex3f(0.5, 0, 1);
		
		// Draw back face:
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(-1, 2, -1);
		glVertex3f(1, 2, -1);
		glVertex3f(1, 0, -1);
		glVertex3f(-1, 0, -1);

		// Draw top side:
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-1, 2, -1);
		glVertex3f(1, 2, -1);
		glVertex3f(0.5, 2, 1);
		glVertex3f(-0.5, 2, 1);

		// Draw bottom side:
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(-1, 0, -1);
		glVertex3f(1, 0, -1);
		glVertex3f(0.5, 0, 1);
		glVertex3f(-0.5, 0, 1);

		glEnd();
		break;
	}
	glPopMatrix();
}

void Building::drawSize(DrawData & data)
{
	switch (grammar[1] % 5)
	{
	case 0:
		size = Matrix4().makeScale(10);
		break;
	case 1:
		size = Matrix4().makeScale(10, 20, 10);
		break;
	case 2:
		size = Matrix4().makeScale(15, 10, 10);
		break;
	case 3:
		size = Matrix4().makeScale(10, 15, 15);
		break;
	case 4:
		size = Matrix4().makeScale(15, 8, 15);
		break;
	}
}

void Building::drawAddition(DrawData & data)
{
	material.apply();

	//Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
	glMatrixMode(GL_MODELVIEW);

	//Push a save state onto the matrix stack, and multiply in the toWorld matrix
	glPushMatrix();
	glMultMatrixf((toWorld * size).ptr());

	switch (grammar[3])
	{
	case 0:
		glBegin(GL_QUADS);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(1.5, 0, -1);
		glVertex3f(0, 0, -1);
		glVertex3f(0, 0, 1);
		glVertex3f(1.5, 0, 1);
		glEnd();


	}

	glPopMatrix();
}

void Building::drawRoof(DrawData & data)
{
	material.apply();

	//Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
	glMatrixMode(GL_MODELVIEW);

	//Push a save state onto the matrix stack, and multiply in the toWorld matrix
	glPushMatrix();
	glMultMatrixf((toWorld * size).ptr());

	switch (grammar[2] % 4)
	{
	case 0:
		switch (grammar[0] % 4)
		{
		case 0:
			glBegin(GL_TRIANGLES);

			// Draw front face:
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(0, 3, 1);
			glVertex3f(1, 2, 1);
			glVertex3f(-1, 2, 1);

			// Draw back face:
			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(0, 3, -1);
			glVertex3f(1, 2, -1);
			glVertex3f(-1, 2, -1);
			glEnd();

			glBegin(GL_QUADS);
			// Draw left side:
			glNormal3f(-1.0, 1.0, 0.0);
			glVertex3f(0, 3, -1);
			glVertex3f(0, 3, 1);
			glVertex3f(-1, 2, 1);
			glVertex3f(-1, 2, -1);

			// Draw right side:
			glNormal3f(1.0, 1.0, 0.0);
			glVertex3f(0, 3, -1);
			glVertex3f(1, 2, -1);
			glVertex3f(1, 2, 1);
			glVertex3f(0, 3, 1);
			glEnd();
			break;

		case 1:
			glBegin(GL_QUADS);
			glNormal3f(0.0, 1.0, 1.0);
			glVertex3f(-0.5, 2.5, 0.5);
			glVertex3f(0.5, 2.5, 0.5);
			glVertex3f(0.5, 2, 1);
			glVertex3f(-0.5, 2, 1);

			glNormal3f(-0.5, 1.0, 0.5);
			glVertex3f(-1, 2.5, 0);
			glVertex3f(-0.5, 2.5, 0.5);
			glVertex3f(-0.5, 2, 1);
			glVertex3f(-1, 2, 0.5);

			glNormal3f(0.5, 1.0, 0.5);
			glVertex3f(0.5, 2.5, 0.5);
			glVertex3f(1, 2.5, 0);
			glVertex3f(1, 2, 0.5);
			glVertex3f(0.5, 2, 1);

			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(-1, 2.5, -1);
			glVertex3f(-1, 2.5, 0);
			glVertex3f(-1, 2, 0.5);
			glVertex3f(-1, 2, -1);

			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(1, 2.5, 0);
			glVertex3f(1, 2.5, -1);
			glVertex3f(1, 2, -1);
			glVertex3f(1, 2, 0.5);

			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(-1, 2.5, -1);
			glVertex3f(1, 2.5, -1);
			glVertex3f(1, 2, -1);
			glVertex3f(-1, 2, -1);
			glEnd();

			glBegin(GL_POLYGON);
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(-1, 2.5, -1);
			glVertex3f(1, 2.5, -1);
			glVertex3f(1, 2.5, 0);
			glVertex3f(0.5, 2.5, 0.5);
			glVertex3f(-0.5, 2.5, 0.5);
			glVertex3f(-1, 2.5, 0);
			glEnd();
			break;

		case 2:
			glBegin(GL_TRIANGLES);
			glNormal3f(-cos(2 * pi / 12), tan(2 * pi / 12), sin(2 * pi / 12));
			glVertex3f(-tan(2 * pi / 12), 3, 0);
			glVertex3f(-1 / cos(2 * pi / 12), 2, 0);
			glVertex3f(-tan(2 * pi / 12), 2, -1);

			glNormal3f(cos(2 * pi / 12), tan(2 * pi / 12), sin(2 * pi / 12));
			glVertex3f(-tan(2 * pi / 12), 3, 0);
			glVertex3f(-1 / cos(2 * pi / 12), 2, 0);
			glVertex3f(-tan(2 * pi / 12), 2, 1);

			glNormal3f(-cos(2 * pi / 12), tan(2 * pi / 12), -sin(2 * pi / 12));
			glVertex3f(tan(2 * pi / 12), 3, 0);
			glVertex3f(1 / cos(2 * pi / 12), 2, 0);
			glVertex3f(tan(2 * pi / 12), 2, -1);

			glNormal3f(cos(2 * pi / 12), tan(2 * pi / 12), -sin(2 * pi / 12));
			glVertex3f(tan(2 * pi / 12), 3, 0);
			glVertex3f(1 / cos(2 * pi / 12), 2, 0);
			glVertex3f(tan(2 * pi / 12), 2, 1);
			glEnd();

			glBegin(GL_QUADS);
			glNormal3f(0, 1, 1);
			glVertex3f(-tan(2 * pi / 12), 3, 0);
			glVertex3f(tan(2 * pi / 12), 3, 0);
			glVertex3f(tan(2 * pi / 12), 2, 1);
			glVertex3f(-tan(2 * pi / 12), 2, 1);

			glNormal3f(0, 1, -1);
			glVertex3f(-tan(2 * pi / 12), 3, 0);
			glVertex3f(tan(2 * pi / 12), 3, 0);
			glVertex3f(tan(2 * pi / 12), 2, -1);
			glVertex3f(-tan(2 * pi / 12), 2, -1);
			glEnd();
			break;

		case 3:
			glBegin(GL_TRIANGLES);

			// Draw front face:
			glNormal3f(0.5, 1.0, 0.5);
			glVertex3f(0.5, 2.5, -0.5);
			glVertex3f(1, 2, -1);
			glVertex3f(0.5, 2, 1);

			// Draw back face:
			glNormal3f(-0.5, 1.0, 0.5);
			glVertex3f(-0.5, 2.5, -0.5);
			glVertex3f(-1, 2, -1);
			glVertex3f(-0.5, 2, 1);;
			glEnd();

			glBegin(GL_QUADS);
			glNormal3f(0.0, 1.0, 2.0);
			glVertex3f(-0.5, 2.5, -0.5);
			glVertex3f(0.5, 2.5, -0.5);
			glVertex3f(0.5, 2, 1);
			glVertex3f(-0.5, 2, 1);

			glNormal3f(0.0, 1.0, -2.0);
			glVertex3f(-1, 2, -1);
			glVertex3f(1, 2, -1);
			glVertex3f(0.5, 2.5, -0.5);
			glVertex3f(-0.5, 2.5, -0.5);
			glEnd();
			break;
		}
		break;

	case 1:
		switch (grammar[0] % 4)
		{
		case 0:
			glBegin(GL_TRIANGLES);

			// Draw front face:
			glNormal3f(0.0, 1.0, 1.0);
			glVertex3f(0, 3, 0);
			glVertex3f(1, 2, 1);
			glVertex3f(-1, 2, 1);

			// Draw back face:
			glNormal3f(0.0, 1.0, -1.0);
			glVertex3f(0, 3, 0);
			glVertex3f(1, 2, -1);
			glVertex3f(-1, 2, -1);

			// Draw left side:
			glNormal3f(-1.0, 1.0, 0.0);
			glVertex3f(0, 3, 0);
			glVertex3f(-1, 2, 1);
			glVertex3f(-1, 2, -1);

			// Draw right side:
			glNormal3f(1.0, 1.0, 0.0);
			glVertex3f(0, 3, 0);
			glVertex3f(1, 2, -1);
			glVertex3f(1, 2, 1);
			glEnd();
			break;

		case 1:
			glBegin(GL_TRIANGLES);
			glNormal3f(-0.5, 1.0, 1.0);
			glVertex3f(0, 3, 0);
			glVertex3f(-0.5, 2, 1);
			glVertex3f(-1, 2, 0.5);

			glNormal3f(0.5, 1.0, 1.0);
			glVertex3f(0, 3, 0);
			glVertex3f(0.5, 2, 1);
			glVertex3f(1, 2, 0.5);

			glNormal3f(0.0, 1.0, 1.0);
			glVertex3f(0, 3, 0);
			glVertex3f(0.5, 2, 1);
			glVertex3f(-0.5, 2, 1);

			glNormal3f(-1.0, 1.0, 0.0);
			glVertex3f(0, 3, 0);
			glVertex3f(-1, 2, -1);
			glVertex3f(-1, 2, 0.5);

			glNormal3f(1.0, 1.0, 0.0);
			glVertex3f(0, 3, 0);
			glVertex3f(1, 2, -1);
			glVertex3f(1, 2, 0.5);

			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(0, 3, 0);
			glVertex3f(-1, 2, -1);
			glVertex3f(1, 2, -1);
			glEnd();
			break;

		case 2:
			glBegin(GL_TRIANGLES);
			glNormal3f(0, 1, 1);
			glVertex3f(0, 3, 0);
			glVertex3f(-tan(2 * pi / 12), 2, 1);
			glVertex3f(tan(2 * pi / 12), 2, 1);

			glNormal3f(0, 1, -1);
			glVertex3f(0, 3, 0);
			glVertex3f(tan(2 * pi / 12), 2, -1);
			glVertex3f(-tan(2 * pi / 12), 2, -1);

			glNormal3f(1 / tan(2 * pi / 12), 1, -1);
			glVertex3f(0, 3, 0);
			glVertex3f(1 / cos(2 * pi / 12), 2, 0);
			glVertex3f(tan(2 * pi / 12), 2, -1);

			glNormal3f(1 / tan(2 * pi / 12), 1, 1);
			glVertex3f(0, 3, 0);
			glVertex3f(1 / cos(2 * pi / 12), 2, 0);
			glVertex3f(tan(2 * pi / 12), 2, 1);

			glNormal3f(-1 / tan(2 * pi / 12), 1, -1);
			glVertex3f(0, 3, 0);
			glVertex3f(-1 / cos(2 * pi / 12), 2, 0);
			glVertex3f(-tan(2 * pi / 12), 2, -1);

			glNormal3f(-1 / tan(2 * pi / 12), 1, 1);
			glVertex3f(0, 3, 0);
			glVertex3f(-1 / cos(2 * pi / 12), 2, 0);
			glVertex3f(-tan(2 * pi / 12), 2, 1);
			glEnd();
			break;

		case 3:
			glBegin(GL_TRIANGLES);

			glNormal3f(0.0, 1.0, 1.0);
			glVertex3f(0, 3, 0);
			glVertex3f(0.5, 2, 1);
			glVertex3f(-0.5, 2, 1);

			glNormal3f(0.0, 1.0, -1.0);
			glVertex3f(0, 3, 0);
			glVertex3f(-1, 2, -1);
			glVertex3f(1, 2, -1);

			glNormal3f(2.0, 1.0, 0.5);
			glVertex3f(0, 3, 0);
			glVertex3f(1, 2, -1);
			glVertex3f(0.5, 2, 1);

			glNormal3f(-2.0, 1.0, 0.5);
			glVertex3f(0, 3, 0);
			glVertex3f(-1, 2, -1);
			glVertex3f(-0.5, 2, 1);
			glEnd();
			break;
		}
		break;
	case 2:
		switch (grammar[0] % 4)
		{
		case 0:
			glBegin(GL_TRIANGLES);

			// Draw front face:
			glNormal3f(1.0, 0.0, 0.0);
			glVertex3f(1, 2.5, -1);
			glVertex3f(1, 2, -1);
			glVertex3f(1, 2, 1);

			// Draw back face:
			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(-1, 2.5, -1);
			glVertex3f(-1, 2, -1);
			glVertex3f(-1, 2, 1);
			glEnd();

			glBegin(GL_QUADS);
			// Draw left side:
			glNormal3f(0.0, 1.0, 0.5);
			glVertex3f(-1, 2.5, -1);
			glVertex3f(1, 2.5, -1);
			glVertex3f(1, 2, 1);
			glVertex3f(-1, 2, 1);

			// Draw right side:
			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(-1, 2.5, -1);
			glVertex3f(1, 2.5, -1);
			glVertex3f(1, 2, -1);
			glVertex3f(-1, 2, -1);
			glEnd();
			break;

		case 1:
			glBegin(GL_QUADS);
			glNormal3f(0.0, 1.0, 1.0);
			glVertex3f(-0.5, 2.5, 0.5);
			glVertex3f(0.5, 2.5, 0.5);
			glVertex3f(0.5, 2, 1);
			glVertex3f(-0.5, 2, 1);

			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(-0.5, 2.5, -1);
			glVertex3f(0.5, 2.5, -1);
			glVertex3f(0.5, 2.5, 0.5);
			glVertex3f(-0.5, 2.5, 0.5);

			glNormal3f(-1.0, 1.0, 0.0);
			glVertex3f(-1, 2, -1);
			glVertex3f(-0.5, 2.5, -1);
			glVertex3f(-0.5, 2.5, 0.5);
			glVertex3f(-1, 2, 0.5);

			glNormal3f(1.0, 1.0, 0.0);
			glVertex3f(0.5, 2.5, -1);
			glVertex3f(1, 2, -1);
			glVertex3f(1, 2, 0.5);
			glVertex3f(0.5, 2.5, 0.5);

			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(-0.5, 2.5, -1);
			glVertex3f(0.5, 2.5, -1);
			glVertex3f(1, 2, -1);
			glVertex3f(-1, 2, -1);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3f(1.0, 1.0, 1.0);
			glVertex3f(0.5, 2.5, 0.5);
			glVertex3f(1, 2, 0.5);
			glVertex3f(0.5, 2, 1);

			glNormal3f(-1.0, 1.0, 1.0);
			glVertex3f(-0.5, 2.5, 0.5);
			glVertex3f(-1, 2, 0.5);
			glVertex3f(-0.5, 2, 1);;
			glEnd();
			break;

		case 2:
			glBegin(GL_TRIANGLES);
			glNormal3f(1 / tan(2 * pi / 12), 1, 1);
			glVertex3f(tan(2 * pi / 12), 2.5, -1);
			glVertex3f(tan(2 * pi / 12), 2, 1);
			glVertex3f(1 / cos(2 * pi / 12), 2, 0);

			glNormal3f(cos(2 * pi / 12), 1, -1);
			glVertex3f(tan(2 * pi / 12), 2.5, -1);
			glVertex3f(1 / cos(2 * pi / 12), 2, 0);
			glVertex3f(tan(2 * pi / 12), 2, -1);

			glNormal3f(-1 / tan(2 * pi / 12), 1, 1);
			glVertex3f(-tan(2 * pi / 12), 2.5, -1);
			glVertex3f(-tan(2 * pi / 12), 2, 1);
			glVertex3f(-1 / cos(2 * pi / 12), 2, 0);

			glNormal3f(-cos(2 * pi / 12), 1, -1);
			glVertex3f(-tan(2 * pi / 12), 2.5, -1);
			glVertex3f(-1 / cos(2 * pi / 12), 2, 0);
			glVertex3f(-tan(2 * pi / 12), 2, -1);;
			glEnd();

			glBegin(GL_QUADS);
			glNormal3f(0, 1, 0.5);
			glVertex3f(-tan(2 * pi / 12), 2.5, -1);
			glVertex3f(tan(2 * pi / 12), 2.5, -1);
			glVertex3f(tan(2 * pi / 12), 2, 1);
			glVertex3f(-tan(2 * pi / 12), 2, 1);

			glNormal3f(0, 0, -1);
			glVertex3f(-tan(2 * pi / 12), 2.5, -1);
			glVertex3f(tan(2 * pi / 12), 2.5, -1);
			glVertex3f(tan(2 * pi / 12), 2, -1);
			glVertex3f(-tan(2 * pi / 12), 2, -1);
			glEnd();
			break;

		case 3:
			glBegin(GL_TRIANGLES);

			// Draw front face:
			glNormal3f(2.0, 2.0, 0.5);
			glVertex3f(0.5, 2.5, -1);
			glVertex3f(1, 2, -1);
			glVertex3f(0.5, 2, 1);

			// Draw back face:
			glNormal3f(-2.0, 2.0, 0.5);
			glVertex3f(-0.5, 2.5, -1);
			glVertex3f(-0.5, 2, 1);
			glVertex3f(-1, 2, -1);
			glEnd();

			glBegin(GL_QUADS);
			glNormal3f(0.0, 1.0, 0.5);
			glVertex3f(-0.5, 2.5, -1);
			glVertex3f(0.5, 2.5, -1);
			glVertex3f(0.5, 2, 1);
			glVertex3f(-0.5, 2, 1);

			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(-0.5, 2.5, -1);
			glVertex3f(0.5, 2.5, -1);
			glVertex3f(1, 2, -1);
			glVertex3f(-1, 2, -1);
			glEnd();
			break;
		}
		break;
	}
	glPopMatrix();
}

void Building::drawDoor(DrawData & data)
{
}

void Building::drawWindow(DrawData & data)
{
}

