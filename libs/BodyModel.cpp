#include "BodyModel.h"

BodyModel::BodyModel(const char *modelFile, vec3f_t origin,
                     double raio,
                     vec3f_t mov_center,
                     double ang_vel,
                     double transl_vel,
                     double elipse_a,
                     double elipse_b,
                     int n_luas,
                     bool interactWithSound,
                     bool interactWithLight) : Body(origin,
                                                    raio,
                                                    mov_center,
                                                    ang_vel,
                                                    transl_vel,
                                                    elipse_a,
                                                    elipse_b,
                                                    n_luas,
                                                    interactWithSound,
                                                    interactWithLight)
{
    this->origin = origin;
    this->raio = raio;

    this->mov_center = mov_center;
    this->ang_vel = ang_vel;
    this->transl_vel = transl_vel;
    this->elipse_a = elipse_a;
    this->elipse_b = elipse_b;
    this->interactWithLight = interactWithLight;
    this->n_luas = n_luas;
    this->interactWithSound = interactWithSound;
    this->transl_angle = 0;
    this->rot_angle = 0;

    vec3f_t scale = {
        .x = raio,
        .y = raio,
        .z = raio};

    this->bModel.scaleModel(&scale);
    this->bModel.loadModel(modelFile);
}

// Função que desenha o modelo
void BodyModel::draw()
{
    this->bModel.renderModel();
}

void BodyModel::move()
{
    // Soma ao angulo na translacao e na rotacao do Body
    this->transl_angle += transl_vel;
    this->rot_angle += ang_vel;

    vec3f_t rot_vec = {
        .x = 0,
        .y = this->rot_angle,
        .z = 0};

    // printf("%0.2f %0.2f \n", this->transl_angle, this->rot_angle);

    if (transl_angle >= 360)
    {
        transl_angle -= 360;
    }
    if (rot_angle >= 360)
    {
        rot_angle -= 360;
    }

    // Utiliza de coordenadas polares para descrever uma elipse
    // X = a * cos (angulo) + x0
    // Y = b * sen (angulo) + y0
    // Z (Nao esta mexida, se for necessario, usa coordenada esferica ou cilindrica >_<

    this->origin.x = mov_center.x + elipse_a * cos(transl_angle * M_PI / 180.0f);
    this->origin.y = 0;
    this->origin.z = mov_center.z + elipse_b * sin(transl_angle * M_PI / 180.0f);

    // Altera as propriedades do modelo
    this->bModel.moveModel(&this->origin);
    // this->bModel.rotateModel(&rot_vec);
}

void BodyModel::move(vec3f_t *aux_mov)
{
    // Soma ao angulo na translacao e na rotacao do Bodya
    this->transl_angle += transl_vel;
    this->rot_angle += ang_vel;

    // printf("%0.2f %0.2f \n", this->transl_angle, this->rot_angle);
    vec3f_t rot_vec = {
        .x = 0,
        .y = this->rot_angle,
        .z = 0};

    if (transl_angle >= 360)
    {
        transl_angle -= 360;
    }
    if (rot_angle >= 360)
    {
        rot_angle -= 360;
    }
    // Utiliza de coordenadas polares para descrever uma elipse
    // Coordenadas do opengl sao diferentes
    // X = a * cos (angulo) + x0
    // Y = 0 (nao mexer se n quiser translacao para cima e para baixo)
    // Z = b * sen (angulo) + y0

    this->origin.x = aux_mov->x + elipse_a * cos(transl_angle * M_PI / 180.0f);
    this->origin.y = 0;
    this->origin.z = aux_mov->z + elipse_b * sin(transl_angle * M_PI / 180.0f);
    // Altera as propriedades do modelo
    this->bModel.moveModel(&this->origin);
    // this->bModel.rotateModel(&rot_vec);

    // printf("MEXEU O MENINE\n ");
}