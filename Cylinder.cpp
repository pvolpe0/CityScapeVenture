#include "Cylinder.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Cylinder::Cylinder() : Drawable(){}

Cylinder::Cylinder(double radius, double height, int slices, int stacks) : Drawable()
{
    this->radius = radius;
    this->height = height;
    this->slices = slices;
    this->stacks = stacks;
    material.color = Color::lightBrown();
}

void Cylinder::draw(DrawData& data)
{
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    //glPushMatrix();
    //glMultMatrixf(toWorld.ptr());
    //if(radius <= 0.2) radius = 0.21;
    gluCylinder(gluNewQuadric(), radius, radius-0.2, height, slices, stacks);
    //gluDisk(gluNewQuadric(), 0, 3, 40, 1);
    
    //glPopMatrix();
}


void Cylinder::update(UpdateData& data)
{
    //
}


