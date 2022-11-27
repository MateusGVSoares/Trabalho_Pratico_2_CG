#include "LightBody.h"
#include "callback.h"

GLfloat var_dif = 0.0f, var_amb = 0.0f, var_spec = 0.0f;
bool lighIsOn = false;

LightBody::LightBody(const char *tex_name,
                     vec3f_t origin,
                     double raio,
                     vec3f_t mov_center,
                     double ang_vel,
                     double transl_vel,
                     double elipse_a,
                     double elipse_b,
                     int n_luas,
                     float *lightAmb,
                     float *lightDif,
                     float *lightSpec,
                     GLuint lightFont) : Body(tex_name,
                                              origin,
                                              raio,
                                              mov_center, ang_vel, transl_vel, elipse_a, elipse_b, n_luas, 0)
{
    memcpy(this->lightAmb, lightAmb, sizeof(float) * 4);
    memcpy(this->lightDif, lightDif, sizeof(float) * 4);
    memcpy(this->lightSpec, lightSpec, sizeof(float) * 4);

    // Seta qual fonte de luz esse corpo ira alterar
    this->lightFont = lightFont;

    if (this->lightFont == GL_LIGHT0)
    {
        var_dif = this->lightDif[0];
        var_amb = this->lightAmb[0];
        var_spec = this->lightSpec[0];
    }

    glEnable(this->lightFont);
}

float *LightBody::getLightDif()
{
    return this->lightDif;
}

float *LightBody::getLightAmb()
{
    return this->lightAmb;
}

float *LightBody::getLightSpec()
{
    return this->lightSpec;
}

void LightBody::draw()
{
    // glColor3f(1.0, 1.0, 1.0);
    lightSourcePos[0] = this->origin.x;
    lightSourcePos[1] = this->origin.y;
    lightSourcePos[2] = this->origin.z;
    lightSourcePos[3] = 1.0;

    if (this->lightFont == GL_LIGHT0)
    {
        if (keyboard.z || keyboard.x)
        {
            var_amb += (keyboard.z - keyboard.x) * 0.01;

            if (var_amb < 0)
            {
                var_amb = 0;
            }
            else if (var_amb > 1.0f)
            {
                var_amb = 1.0f;
            }

            this->lightAmb[0] = var_amb;
            this->lightAmb[1] = var_amb;
            this->lightAmb[2] = var_amb;
        }
        if (keyboard.c || keyboard.v)
        {
            var_dif += (keyboard.c - keyboard.v) * 0.01;

            if (var_dif < 0)
            {
                var_dif = 0;
            }
            else if (var_dif > 1.0f)
            {
                var_dif = 1.0f;
            }

            this->lightDif[0] = var_dif;
            this->lightDif[1] = var_dif;
            this->lightDif[2] = var_dif;
        }
        if (keyboard.b || keyboard.n)
        {
            var_spec += (keyboard.b - keyboard.n) * 0.01;

            if (var_spec < 0.0f)
            {
                var_spec = 0.0f;
            }
            else if (var_spec > 1.0f)
            {
                var_spec = 1.0f;
            }

            this->lightSpec[0] = var_spec;
            this->lightSpec[1] = var_spec;
            this->lightSpec[2] = var_spec;
        }

        glLightfv(this->lightFont, GL_POSITION, this->lightSourcePos);
        glLightfv(this->lightFont, GL_AMBIENT, this->lightAmb);
        glLightfv(this->lightFont, GL_DIFFUSE, this->lightDif);
        glLightfv(this->lightFont, GL_SPECULAR, this->lightSpec);
    }
    else if (lighIsOn)
    {
        this->interactWithLight = true;
        glLightfv(this->lightFont, GL_POSITION, this->lightSourcePos);
        glLightfv(this->lightFont, GL_AMBIENT, this->lightAmb);
        glLightfv(this->lightFont, GL_DIFFUSE, this->lightDif);
        glLightfv(this->lightFont, GL_SPECULAR, this->lightSpec);
    }
    else
    {
        this->interactWithLight = false;
    }

    glPushMatrix();

    glTranslatef(this->origin.x, this->origin.y, this->origin.z);

    // Rotaciona em torno do eixo y, pois o y é o eixo para cima no ngc
    glRotatef(-this->rot_angle, 0, 1, 0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[0]);

    solidSphere(this->raio, DEF_STACKS, DEF_COLS);

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
