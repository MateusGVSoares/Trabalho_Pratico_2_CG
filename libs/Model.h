// STL Libs
#include <vector>
#include <map>
#include <string.h>
#include <iostream>
#include <fstream>

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
    float difusse[4];
    float specular[4];
    float shine[4];
} material_t;

typedef struct mesh
{
    std::vector<vertex_t> vertices;
    std::string use_material;
} mesh_t;

class Model
{
private:
    vec3f_t origin;
    vec3f_t rot_vec;

    // Faz uma lista de mesh/grupos de poligonos
    std::vector<mesh_t> mesh_list;

    // Faz um map de materiais
    std::map<std::string, material_t> mat_map;

public:
    // Model();
    // ~Model();

    // Função para rotacionar o modelo
    // void rotateModel(vec3f_t *rot);

    // Função para transladar o modelo
    // void moveModel(vec3f_t *mov);

    // Função para carregar o modelo
    void loadModel(const char *fname);

    // Função para renderizar o modelo
    // void renderModel();
};