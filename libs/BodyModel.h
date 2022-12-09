#ifndef __BODYMODEL__
#define __BODYMODEL__
#include "Body.h"
#include "Model.h"

class BodyModel : public Body
{
private:
    Model bModel;

public:
    using Body::Body;
    BodyModel(const char *modelFile, vec3f_t origin,
              double raio,
              vec3f_t mov_center,
              double ang_vel,
              double transl_vel,
              double elipse_a,
              double elipse_b,
              int n_luas,
              bool interactWithSound,
              bool interactWithLight);
    void draw() override;
    void move() override;
    void move(vec3f_t *aux_mov) override;
};

#endif