#include "Model.h"

// Parser para um .obj
void Model::loadModel(const char *fname)
{

    // Carrega os vertices, normais e indices

    // Indices
    // Indices de vertices
    std::vector<int> index_position;

    // Indices de normais
    std::vector<int> index_normal;

    // Indices de textura
    std::vector<int> index_tex;

    // Vetores
    // Vetores de vertices
    std::vector<vec3f_t> vec_position;

    // Vetores de normais
    std::vector<vec3f_t> vec_normal;

    // Vetores de coordenadas de texturas
    std::vector<vec2f_t> vec_texturas;
}