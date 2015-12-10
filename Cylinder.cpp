#include "Cylinder.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Cylinder::Cylinder(double radius, int slices, int stacks) : Drawable()
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
}

void Cylinder::draw(DrawData& data)
{
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    //gluCylinder(radius, slices, stacks);
    
    glPopMatrix();
}


void Cylinder::update(UpdateData& data)
{
    //
}


