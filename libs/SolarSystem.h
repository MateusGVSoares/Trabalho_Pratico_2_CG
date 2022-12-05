#ifndef __SOLARSYSTEM__
#define __SOLARSYSTEM__

#include <vector>
#include "Body.h"
#include "LightBody.h"
#include <iostream>
#include <memory>
#include <stack>
#include "vec3f.h"

class SolarSystem
{
private:
    // Vetores de Corpos no Sistema
    std::vector<std::shared_ptr<Body>> astros;

    // Vetores de corpos que nao precisam de iteracao com a luz
    std::vector<Body *> aux_light;

    // Stack para auxiliar na atualizacao do movimento dos astros
    std::unique_ptr<std::stack<std::pair<vec3f_t, int>>> centerStack;

    int skyBoxTexture;

public:
    std::vector<vec3f_t *> aux_sound;
    SolarSystem(const char *script_name);

    // Parser para o script de sistema solar
    int parseScript(const char *script_name);

    // Funcao para atualizar o movimento dos astros
    void updateOnTime();

    // Funcao para desenhar os astros
    void updateOnDraw();

    void drawSkyBox();
};

#endif