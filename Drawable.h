#ifndef CSE167_Drawable_h
#define CSE167_Drawable_h

<<<<<<< HEAD


=======
>>>>>>> 683fb8ff0292346d4d451c017891821ca3f566bd
#define PI 3.14159263538979323846

#include <iostream>
#include "Matrix4.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Material.h"
#include <float.h>
#include <math.h>
#include <vector>


class Drawable
{
    
public:
    
    Matrix4 toWorld;
    Material material;

    
    Drawable(void);
    ~Drawable(void);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
};

#endif
