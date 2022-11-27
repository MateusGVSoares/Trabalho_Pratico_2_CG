#include "Body.h"


void solidSphere(int radius, int stacks, int columns)
{
    // cria uma quádrica
    GLUquadric *quadObj = gluNewQuadric();
    // estilo preenchido... poderia ser GLU_LINE, GLU_SILHOUETTE
    // ou GLU_POINT
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    // chama 01 glNormal para cada vértice.. poderia ser
    // GLU_FLAT (01 por face) ou GLU_NONE
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    // chama 01 glTexCoord por vértice
    gluQuadricTexture(quadObj, GL_TRUE);
    // cria os vértices de uma esfera
    gluSphere(quadObj, radius, stacks, columns);
    // limpa as variáveis que a GLU usou para criar
    // a esfera
    gluDeleteQuadric(quadObj);
}

Body::Body(const char *tex_name,
           vec3f_t origin,
           double raio,
           vec3f_t mov_center,
           double ang_vel,
           double transl_vel,
           double elipse_a,
           double elipse_b,
           int n_luas,
           bool interactWithLight)
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

    this->transl_angle = 0;
    this->rot_angle = 0;

    this->texture = new Texturazer(tex_name);

    // Muda o material do Body de acordo com os parametros da textura
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, this->texture->matDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, this->texture->matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, this->texture->matShine);
}

Body::~Body()
{
    if (this->texture != NULL)
    {
        delete this->texture;
    }
}

void Body::draw()
{
    glPushMatrix();

    // printf("X = %0.2f | Y = %0.2f | Z = %0.2f \n",origin.x, origin.y, origin.z);

    // A origem é translada na move()
    // Usa de coordenadas de elipse para transladar
    glTranslatef(origin.x, origin.y, origin.z);

    // Rotaciona em torno do proprio eixo y
    // Y é o eixo para cima nas coordenadas do OpenGl, logo rotaciona no Y
    glRotatef(-this->rot_angle, 0, 1, 0);

    // glColor3f(1.0, 1.0, 1.0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[0]);

    solidSphere(this->raio, DEF_STACKS, DEF_COLS);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void Body::move(vec3f_t *aux_mov)
{
    // Soma ao angulo na translacao e na rotacao do Bodya
    this->transl_angle += transl_vel;
    this->rot_angle += ang_vel;

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

    this->origin.x = aux_mov->x + elipse_a * cos(transl_angle * M_PI / 180.0f);
    this->origin.y = 0;
    this->origin.z = aux_mov->z + elipse_b * sin(transl_angle * M_PI / 180.0f);
}

void Body::move()
{
    // Soma ao angulo na translacao e na rotacao do Body
    this->transl_angle += transl_vel;
    this->rot_angle += ang_vel;

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
}

vec3f_t *Body::getOrigin()
{
    return &this->origin;
}

bool Body::isLight()
{
    return this->interactWithLight;
}