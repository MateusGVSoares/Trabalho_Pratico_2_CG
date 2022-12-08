#include "Model.h"

// Parser para um .obj
void Model::loadModel(const char *fname)
{

    // Carrega os vertices, normais e indices

    // Indices
    std::vector<uint> index_position, // Indices de vertices
        index_normal,                 // Indices de normais
        index_tex;                    // Indices de textura

    // Vetores
    std::vector<vec3f_t> vec_position, // Vetores de vertices
        vec_normal;                    // Vetores de normais

    std::vector<vec2f_t> vec_texturas; // Vetores de coordenadas de texturas

    // Vetores auxiliares para leitura
    vec3f_t v3 = {0};
    vec2f_t v2 = {0};

    // Variaveis auxiliares para leitura dos indices
    int c1, c2, c3,
        mesh_counter = -1; // Contador das mesh, inicializa em menos um pq todo .obj começa já com um header 'o' indicando a geração de uma mesh

    // Vertice auxiliar
    vertex_t aux_vertex = {0};

    std::ifstream file;
    std::string header, readl;
    char *aux_string = new char[200];


    mesh_list.clear();

    // Tenta abrir o arquivo
    file.open(fname);
    if (!file.is_open())
    {
        printf("Não conseguiu abrir o arquivo [%s] \n", fname);
        return;
    }

    while (file.peek() != EOF)
    {
        // Obtem o header
        std::getline(file, header, ' ');

        // Verifica o tipo de dado q está lendo
        if(header == "o")
        {
            // Incrementa o contador de mesh 
            mesh_counter++;

            // Verifica se deve incrementar ou não o vetor de mesh
            if(mesh_counter >= mesh_list.size())
            {
                mesh_list.resize(mesh_counter + 1);
            }
        }
        else if (header == "v") // Ponto
        {
            // Lê as coordenadas do ponto
            std::getline(file, readl);
            sscanf(readl.c_str(), "%f %f %f", &v3.x, &v3.y, &v3.y);
            vec_position.push_back(v3);
        }
        else if (header == "vt") // Textura
        {
            // Lê as coordenadas de textura
            std::getline(file, readl);
            sscanf(readl.c_str(), "%f %f", &v2.x, &v2.y);
            vec_texturas.push_back(v2);
        }
        else if (header == "vn") // Normal
        {
            // Lê a coordenada de normal
            std::getline(file, readl);
            sscanf(readl.c_str(), "%f %f %f", &v3.x, &v3.y, &v3.z);
            vec_normal.push_back(v3);
        }
        else if (header == "f")
        {
            while (file.peek() >= '0' && file.peek() <= '9')
            {
                // Posicao - Textura - Normal
                std::getline(file, readl, ' ');
                sscanf(readl.c_str(), "%d/%d/%d", &c1, &c2, &c3);

                // Pega os indexs e coloca nos vetores
                index_position.push_back(c1);
                index_tex.push_back(c2);
                index_normal.push_back(c3);
            }
        }
        else if(header == "#")
        {

        }
    }

    for (int i = 0; i < index_position.size(); i++)
    {
        // Indexa todos os vertices
        // Subtrai 1 porque os vértices começam em 1 em .obj 
        aux_vertex.point = vec_position[index_position[i] - 1];
        aux_vertex.tex_cord = vec_texturas[index_tex[i] - 1];
        aux_vertex.normal = vec_normal[index_normal[i] - 1];
        vertices.push_back(aux_vertex);
    }

    delete aux_string;
}