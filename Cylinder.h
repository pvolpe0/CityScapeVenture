#ifndef CSE167_Cylinder_h
#define CSE167_Cylinder_h

#include <iostream>
#include "Drawable.h"

class Cylinder : public Drawable
{
    
public:
    
    double radius, height;
    int slices, stacks;
    
    Cylinder(double, double, int, int);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
};

#endif
