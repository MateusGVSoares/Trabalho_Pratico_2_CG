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
    double last_x;
    double last_y;
    vec3f_t direction;
    vec3f_t side;

public:
    vec3f_t origin;
    Camera(vec3f_t origin, double sense);
    void updateCamera();
    void use();
};

#endif