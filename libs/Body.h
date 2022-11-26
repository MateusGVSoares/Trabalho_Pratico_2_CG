#ifndef __BODY__
#define __BODY__

#include "Texturazer.h"

// Parâmetros:
// Raio do corpo,
// velocidade de rotação
// velocidade translação
// reflexão da textura

void solidSphere(int radius, int stacks, int columns);

// Constantes para desenho dos circulos
#define DEF_STACKS 160
#define DEF_COLS 160

class Body
{

protected:
    // Parametros para definir a esfera
    vec3f_t origin;
    double raio;

    // Textura
    Texturazer *texture;

    // Parametros para translacao, rotacao e orbitas elipticas
    vec3f_t mov_center;
    double ang_vel;
    double transl_vel;
    double rot_angle;
    double transl_angle;
    double elipse_a;
    double elipse_b;
    GLuint interactWithLight;

public:
    int n_luas;
    Body(const char *tex_name,
         vec3f_t origin,
         double raio,
         vec3f_t mov_center,
         double ang_vel,
         double transl_vel,
         double elipse_a,
         double elipse_b,
         int n_luas,
         bool interactWithLight);
    ~Body();
    virtual void draw();
    void move();
    void move(vec3f_t *aux_mov);
    bool isLight();
    vec3f_t *getOrigin();
};

#endif