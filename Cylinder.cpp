#include "Cylinder.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Cylinder::Cylinder(double radius, double height, int slices, int stacks) : Drawable()
{
    this->radius = radius;
    this->height = height;
    this->slices = slices;
    this->stacks = stacks;
}

void Cylinder::draw(DrawData& data)
{
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    gluCylinder(gluNewQuadric(), radius, radius, height, slices, stacks);
    //gluDisk(gluNewQuadric(), 0, 3, 40, 1);
    
    glPopMatrix();
}


void Cylinder::update(UpdateData& data)
{
    //
}


