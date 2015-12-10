#include "Skybox.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define SKYBOX_LENGTH 1000

Skybox::Skybox()
{

}

void Skybox::draw()
{
	// set the current drawing color to white to use original texture colors
	glColor3f(1, 1, 1);

	{	// front
		front->bind();

		/* draw quad, takes 4 vertices */
		glBegin(GL_QUADS);



		// specify texture coordinates for each vertex
		// note that textures are stored "upside down"
		glTexCoord2f(0, 1); glVertex3f(-SKYBOX_LENGTH, -SKYBOX_LENGTH, -SKYBOX_LENGTH);
		glTexCoord2f(1, 1); glVertex3f(SKYBOX_LENGTH, -SKYBOX_LENGTH, -SKYBOX_LENGTH);
		glTexCoord2f(1, 0); glVertex3f(SKYBOX_LENGTH, SKYBOX_LENGTH, -SKYBOX_LENGTH);
		glTexCoord2f(0, 0); glVertex3f(-SKYBOX_LENGTH, SKYBOX_LENGTH, -SKYBOX_LENGTH);

		/* tell OpenGL we're done drawing quads */
		glEnd();

		front->unbind();
	}

	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Use bilinear interpolation:
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	{	// left
		left->bind();

		// draw quad, takes 4 vertices 
		glBegin(GL_QUADS);



		// specify texture coordinates for each vertex
		// note that textures are stored "upside down"
		glTexCoord2f(0, 0); glVertex3f(-SKYBOX_LENGTH, SKYBOX_LENGTH, SKYBOX_LENGTH );
		glTexCoord2f(1, 0); glVertex3f(-SKYBOX_LENGTH, SKYBOX_LENGTH, -SKYBOX_LENGTH);
		glTexCoord2f(1, 1); glVertex3f(-SKYBOX_LENGTH, -SKYBOX_LENGTH, -SKYBOX_LENGTH);
		glTexCoord2f(0, 1); glVertex3f(-SKYBOX_LENGTH, -SKYBOX_LENGTH, SKYBOX_LENGTH);

		// tell OpenGL we're done drawing quads 
		glEnd();

		left->unbind();
	}

	{	// right
		right->bind();

		// draw quad, takes 4 vertices 
		glBegin(GL_QUADS);



		// specify texture coordinates for each vertex
		// note that textures are stored "upside down"
		glTexCoord2f(0, 0); glVertex3f(SKYBOX_LENGTH, SKYBOX_LENGTH, -SKYBOX_LENGTH);
		glTexCoord2f(1, 0); glVertex3f(SKYBOX_LENGTH, SKYBOX_LENGTH, SKYBOX_LENGTH);
		glTexCoord2f(1, 1); glVertex3f(SKYBOX_LENGTH, -SKYBOX_LENGTH, SKYBOX_LENGTH);
		glTexCoord2f(0, 1); glVertex3f(SKYBOX_LENGTH, -SKYBOX_LENGTH, -SKYBOX_LENGTH);

		// tell OpenGL we're done drawing quads 
		glEnd();

		right->unbind();

	}

	{	// top
		top->bind();

		// draw quad, takes 4 vertices 
		glBegin(GL_QUADS);



		// specify texture coordinates for each vertex
		// note that textures are stored "upside down"
		glTexCoord2f(1, 1); glVertex3f(-SKYBOX_LENGTH, SKYBOX_LENGTH, -SKYBOX_LENGTH);
		glTexCoord2f(1, 0); glVertex3f(SKYBOX_LENGTH, SKYBOX_LENGTH, -SKYBOX_LENGTH);
		glTexCoord2f(0, 0); glVertex3f(SKYBOX_LENGTH, SKYBOX_LENGTH, SKYBOX_LENGTH );
		glTexCoord2f(0, 1); glVertex3f(-SKYBOX_LENGTH, SKYBOX_LENGTH, SKYBOX_LENGTH );

		// tell OpenGL we're done drawing quads 
		glEnd();

		top->unbind();
	}

	{	// base
		base->bind();

		// draw quad, takes 4 vertices 
		glBegin(GL_QUADS);



		// specify texture coordinates for each vertex
		// note that textures are stored "upside down"
		glTexCoord2f(0, 0); glVertex3f(-SKYBOX_LENGTH, -SKYBOX_LENGTH, -SKYBOX_LENGTH);
		glTexCoord2f(1, 0); glVertex3f(SKYBOX_LENGTH, -SKYBOX_LENGTH, -SKYBOX_LENGTH);
		glTexCoord2f(1, 1); glVertex3f(SKYBOX_LENGTH, -SKYBOX_LENGTH, SKYBOX_LENGTH);
		glTexCoord2f(0, 1); glVertex3f(-SKYBOX_LENGTH, -SKYBOX_LENGTH, SKYBOX_LENGTH);

		// tell OpenGL we're done drawing quads 
		glEnd();

		base->unbind();
	}


	{	// back
		back->bind();

		// draw quad, takes 4 vertices 
		glBegin(GL_QUADS);



		// specify texture coordinates for each vertex
		// note that textures are stored "upside down"
		glTexCoord2f(0, 0); glVertex3f(SKYBOX_LENGTH, SKYBOX_LENGTH, SKYBOX_LENGTH );
		glTexCoord2f(1, 0); glVertex3f(-SKYBOX_LENGTH, SKYBOX_LENGTH, SKYBOX_LENGTH );
		glTexCoord2f(1, 1); glVertex3f(-SKYBOX_LENGTH, -SKYBOX_LENGTH, SKYBOX_LENGTH );
		glTexCoord2f(0, 1); glVertex3f(SKYBOX_LENGTH, -SKYBOX_LENGTH, SKYBOX_LENGTH );

		// tell OpenGL we're done drawing quads 
		glEnd();

		back->unbind();
	}
	
}




