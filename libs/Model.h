#ifndef __MODEL__
#define __MODEL__
// STL Libs
#include <vector>
#include <map>
#include <string.h>
#include <iostream>
#include <fstream>
#include <SOIL/SOIL.h>

// OGL libs
#include <GL/gl.h>

// Our Libs
#include "vec3f.h"

// TODO:
/*
    - Carregar os vetores normais, as coordenadas de textura e os vertices
    - Gerar as faces do poligono
    - Gerar uma indexizacao valida -> Usa de algoritmo com o mapa para carregar com VBO
*/

typedef struct vertex
{
    vec3f_t point;    // Coordenadas do vértice
    vec2f_t tex_cord; // Coordenadas da textura
    vec3f_t normal;   // Vetor normal
} vertex_t;

typedef struct material
{
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float shine[4];
    GLint texture;
} material_t;

class Model
{
private:
    vec3f_t origin;
    vec3f_t rot_vec;
    vec3f_t scale;
    // Vetor de Call Lists que devem ser renderizadas
    std::vector<GLuint> cList;

    // Armazena um vetor de texturas carregadas para liberar essa memória depois
    std::vector<uint> loaded_textures;

public:
    Model();

    ~Model();

    void scaleModel(vec3f_t * scale_vec);
    
    // Função para rotacionar o modelo
    void rotateModel(vec3f_t *rot);

    // Função para transladar o modelo
    void moveModel(vec3f_t *mov);

    // Função para carregar o modelo
    void loadModel(const char *fname);

    // Função para renderizar o modelo
    void renderModel();
};
#endif