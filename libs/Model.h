// STL Libs
#include <vector>
#include <map>
#include <iostream>
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

typedef struct vertex{
    vec3f_t point;      // Coordenadas do vértice
    vec2f_t tex_cord;   // Coordenadas da textura
    vec3f_t normal;     // Vetor normal
} vertex_t;

class Model
{
    vec3f_t origin;
    vec3f_t rot_vec;

    std::vector<vertex_t> vertices;

public:
    Model();
    ~Model();

    // Função para rotacionar o modelo
    void rotateModel(vec3f_t *rot);

    // Função para transladar o modelo
    void moveModel(vec3f_t *mov);

    // Função para carregar o modelo
    void loadModel(const char *fname);

    // Função para renderizar o modelo
    void renderModel();
};