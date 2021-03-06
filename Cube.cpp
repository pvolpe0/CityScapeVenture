#include "Cube.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"

Cube::Cube(float size) : Drawable()
{
    this->size = size;
	doorColor = Color::randomPastel();
	windowColor = Color::randomPastel();
}

Cube::~Cube()
{
    //Delete any dynamically allocated memory/objects here
}


void Cube::draw(DrawData& data)
{
    float halfSize = size/2.0;
    
    //Apply the material properties
    //From here forward anything drawn will be drawn with this material
    material.apply();
    
    //Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
    glMatrixMode(GL_MODELVIEW);
    
    //Push a save state onto the matrix stack, and multiply in the toWorld matrix
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    //Make cube!
    //Note: The glBegin, and glEnd should always be as close to the glNormal/glVertex calls as possible
    //These are special calls that 'freeze' many internal states of OpenGL.
    //Once the glBegin state is active many of the calls made to OpenGL (like glMultMatrixf) will be IGNORED!
    //As a good habit, only call glBegin just before you need to draw, and call end just after you finish
    glBegin(GL_QUADS);
    
    // Draw front face:
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-halfSize,  halfSize * 4,  halfSize);
    glVertex3f( halfSize,  halfSize * 4,  halfSize);
    glVertex3f( halfSize, 0,  halfSize);
    glVertex3f(-halfSize, 0,  halfSize);
    
    // Draw left side:
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-halfSize,  halfSize * 4,  halfSize);
    glVertex3f(-halfSize,  halfSize * 4, -halfSize);
    glVertex3f(-halfSize, 0, -halfSize);
    glVertex3f(-halfSize, 0,  halfSize);
    
    // Draw right side:
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f( halfSize,  halfSize * 4,  halfSize);
    glVertex3f( halfSize,  halfSize * 4, -halfSize);
    glVertex3f( halfSize, 0, -halfSize);
    glVertex3f( halfSize, 0,  halfSize);
    
    // Draw back face:
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-halfSize,  halfSize * 4, -halfSize);
    glVertex3f( halfSize,  halfSize * 4, -halfSize);
    glVertex3f( halfSize, 0, -halfSize);
    glVertex3f(-halfSize, 0, -halfSize);
    
    // Draw top side:
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-halfSize,  halfSize * 4,  halfSize);
    glVertex3f( halfSize,  halfSize * 4,  halfSize);
    glVertex3f( halfSize,  halfSize * 4, -halfSize);
    glVertex3f(-halfSize,  halfSize * 4, -halfSize);
    
    // Draw bottom side:
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-halfSize, 0, -halfSize);
    glVertex3f( halfSize, 0, -halfSize);
    glVertex3f( halfSize, 0,  halfSize);
    glVertex3f(-halfSize, 0,  halfSize);

	// Draw Door:
    
    glEnd();
    
	glColor3fv(doorColor.ptr());
    glBegin(GL_QUADS);

	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-halfSize / 3, halfSize, halfSize + .05);
	glVertex3f(halfSize / 3, halfSize, halfSize + .05);
	glVertex3f(halfSize / 3, 0, halfSize + .05);
	glVertex3f(-halfSize / 3, 0, halfSize + .05);

    glEnd();

	glColor3fv(windowColor.ptr());
    glBegin(GL_QUADS);

	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(halfSize / 3, halfSize *  3, halfSize + .05);
	glVertex3f(2 * halfSize / 3, halfSize * 3, halfSize + .05);
	glVertex3f(2 * halfSize / 3, halfSize * 8 / 3, halfSize + .05);
	glVertex3f(halfSize / 3, halfSize * 8 / 3, halfSize + .05);

    glEnd();

    //The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
    //glutSolidCube(size);
    
    //Pop the save state off the matrix stack
    //This will undo the multiply we did earlier
    glPopMatrix();
}


void Cube::update(UpdateData& data)
{
    //
}

void Cube::spin(float radians)
{
    Matrix4 rotation;
    rotation.makeRotateY(radians);
}

