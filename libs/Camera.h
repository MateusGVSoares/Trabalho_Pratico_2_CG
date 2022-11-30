#ifndef __CAMERA__
#define __CAMERA__

#include "GL/freeglut.h"
#include "callback.h"
#include "vec3f.h"
#include "math.h"

class Camera
{
private:
    double pitch; // Rotação no eixo Z
    double roll;  // Rotação no eixo X
    double yaw;   // Rotação no eixo y
    double sense;
    vec3f_t direction;

public:
    vec3f_t origin;
    Camera(vec3f_t origin, double sense);
    void updateCamera();
    void use();
};

#endif