#include "SolarSystem.h"

SolarSystem::SolarSystem(const char *script)
{
    if (this->parseScript(script))
    {
        printf("Deu ruim no parser do sistema solar >_<  \n");
    }
    // Aloca a memoria da stack com unique_ptr
    this->centerStack = std::make_unique<std::stack<std::pair<vec3f_t, int>>>();

    skyBoxTexture = SOIL_load_OGL_texture("assets/texture/stars_milky_way.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_DDS_LOAD_DIRECT);
}

int SolarSystem::parseScript(const char *file_name)
{
    // Referência para o arquivo
    std::ifstream *file = new std::ifstream();

    // Variaveis auxiliares
    vec3f_t mov_origem = {0};

    GLint lightEmissor = 0,
          interactWithSound = 0,
          interactWithLight = 0,
          n_luas = 0,
          n_astros = 0;

    GLfloat vel_rot = 0, elipse_a, elipse_b,
            vel_trans = 0, radius = 0;

    char *input_str = (char *)malloc(sizeof(char) * 50);
    char *tex_name = (char *)malloc(sizeof(char) * 50);

    float lightAmb[4] = {0};
    float lightSpec[4] = {0};
    float lightDif[4] = {0};

    GLuint n_fonts = 0;

    // Abro o arquivo
    file->open(file_name, std::ios::in);

    // Verifica se o arquivo foi aberto
    if (!file->is_open())
    {
        printf("COULDNT_OPEN_FILE \n");
        delete input_str;
        delete file;
        return 1;
    }

    // Verifica se o arquivo está vazio
    if (!file->eof())
    {
        file->getline(input_str, 30);

        // Verifica a formatacao
        if (strcmp("SISTEMA", input_str))
        {
            printf("FORMAT_ERROR_ON_FILE \n");
            delete input_str;
            delete tex_name;
            delete file;
            return 1;
        }
    }
    else
    {
        delete input_str;
        delete tex_name;
        delete file;
        return 1;
    }

    // Verifica quantos astros teremos
    file->getline(input_str, 30);
    sscanf(input_str, "%d", &n_astros);

    printf("Ira criar %d astros \n", n_astros);

    for (int i = 0; i < n_astros; i++)
    {
        // limpa a flag de emissor de luz
        lightEmissor = 0;
        mov_origem.x = 0;
        mov_origem.y = 0;
        mov_origem.z = 0;

        /*
            centro de movimento,
            raio,
            elipse_a,
            elipse_b,
            velocidade de rotacao,
            velocidade de translacao,
            emissao de luz,
            numero de luas ,
            script da textura
        */

        // Diminui a flag para analise de orbita
        // Obter o centro de movimento (x, y, z)
        file->getline(input_str, 30, ';');
        sscanf(input_str, "%f,%f,%f", &mov_origem.x, &mov_origem.y, &mov_origem.z);

        // Obtem o raio do corpo
        file->getline(input_str, 10, ';');
        sscanf(input_str, "%f", &radius);

        // Obter os coeficientes "a" e "b" das elipses
        file->getline(input_str, 10, ';');
        sscanf(input_str, "%f", &elipse_a);
        file->getline(input_str, 10, ';');
        sscanf(input_str, "%f", &elipse_b);

        // Obter velocidade de rotação
        file->getline(input_str, 10, ';');
        sscanf(input_str, "%f", &vel_rot);

        // Obter velocidade de translação
        file->getline(input_str, 10, ';');
        sscanf(input_str, "%f", &vel_trans);

        // Obter propriedade de emissor de luz
        file->getline(input_str, 10, ';');
        sscanf(input_str, "%d", &lightEmissor);

        // Verifica se é um emissor de Luz
        if (lightEmissor)
        {
            // Carrega as propriedades da luz
            file->getline(input_str, 100, ';');
            sscanf(input_str, "%f,%f,%f", &lightAmb[0], &lightAmb[1], &lightAmb[2]);
            file->getline(input_str, 100, ';');
            sscanf(input_str, "%f,%f,%f", &lightDif[0], &lightDif[1], &lightDif[2]);
            file->getline(input_str, 100, ';');
            sscanf(input_str, "%f,%f,%f", &lightSpec[0], &lightSpec[1], &lightSpec[2]);

            lightAmb[3] = lightSpec[3] = lightDif[3] = 1.0;
        }

        // Obter o número de luas
        file->getline(input_str, 10, ';');
        sscanf(input_str, "%d", &n_luas);

        // Verifica se interage com a luz
        file->getline(input_str, 20, ';');
        sscanf(input_str, "%d", &interactWithLight);

        // Pegar o nome do script de textura
        file->getline(tex_name, 100, ';');

        // Cria o objeto como um corpo ou como emissor de luz
        if (lightEmissor)
        {
            printf(" -- Criou um corpo Luminoso \n");
            astros.push_back(std::make_shared<LightBody>(tex_name, mov_origem, radius, mov_origem, vel_rot,
                                                         vel_trans, elipse_a, elipse_b, n_luas, interactWithLight, lightAmb, lightDif, lightSpec, GL_LIGHT0 + n_fonts));
            n_fonts++;
        }
        else
        {
            printf(" -- Criou um corpo \n");
            astros.push_back(std::make_shared<Body>(tex_name, mov_origem, radius, mov_origem, vel_rot,
                                                    vel_trans, elipse_a, elipse_b, n_luas, interactWithSound, interactWithLight));
        }

        printf("Centro do Movimento : %0.2f %0.2f %0.2f \nRaio do Planeta : %0.2f \n A: %0.2f B: %0.2f \n VelRot: %0.2f | VelTrans: %0.2f\n Emissor de Luz : %d\n Numero de Luas : %d\n Interage com a luz:%d\n Script de Textura : %s\n",
               mov_origem.x,
               mov_origem.y,
               mov_origem.z,
               radius,
               elipse_a,
               elipse_b,
               vel_rot,
               vel_trans,
               lightEmissor,
               n_luas,
               interactWithLight,
               tex_name);
        // Lê o resto da linha
        // file->getline(input_str, 1);
    }

    delete input_str;
    delete tex_name;
    delete file;

    return 0;
}

void SolarSystem::updateOnTime()
{
    vec3f_t *body_mov;

    // Atualiza o movimento de todos os astros
    for (int i = 0, aux_orbit = 0; i < astros.size(); i++)
    {
        // printf("-> Numero de planetas a atualizar : %d \n", astros.size());
        if (centerStack->empty())
        {
            // printf("Stack Vazia\n");
            // Movimenta o planeta com seu centro localizado em mov_center definido
            astros[i]->move();
        }
        else
        {
            centerStack->top().second--;

            astros[i]->move(body_mov);

            // Verifica se ainda deve usar aquele centro
            if (!centerStack->top().second)
            {
                // Desempilha aquele centro
                centerStack->pop();
                // Verifica se ainda há um centro a ser calculado
                if (!centerStack->empty())
                    body_mov = &centerStack->top().first;
                else
                    body_mov = NULL;
            }
        }

        // Verifica se o planeta possui objetos que o orbitam
        if (astros[i]->n_luas)
        {
            // Ira continuar na stack por n_luas
            aux_orbit = astros[i]->n_luas;
            body_mov = astros[i]->getOrigin();

            centerStack->push(std::make_pair(*body_mov, aux_orbit));
        }
    }
}

void SolarSystem::drawSkyBox()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, skyBoxTexture);

    solidSphere(1800, DEF_STACKS, DEF_COLS);
    glDisable(GL_TEXTURE_2D);
}

void SolarSystem::updateOnDraw()
{
    vec3f_t aux;

    // Limpa o vetor de objetos que nao reagem a luz
    aux_light.clear();
    aux_sound.clear();

    // Desenha todos os objetos que reagem a luz
    glEnable(GL_LIGHTING);
    for (int i = 0; i < astros.size(); i++)
    {
        // Verifica se o corpo interage com a luz
        if (astros[i]->isLight())
        {
            astros[i]->draw();
        }
        else
        {
            aux_light.push_back(astros[i].get());
        }

        if (astros[i]->withSound())
        {
            aux_sound.push_back(astros[i].get());
        }
    }
    glDisable(GL_LIGHTING);

    // Desenha os objetos que nao reagem a luz
    for (int i = 0; i < aux_light.size(); i++)
        aux_light[i]->draw();
}