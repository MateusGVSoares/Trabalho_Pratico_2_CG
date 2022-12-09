#include "Model.h"

// Parser para um .obj
void Model::loadModel(const char *fname)
{
    printf("\n\n\n");
    // Variavel auxiliar para indicar que está atualmente carregando uma mesh na memoria
    bool generating_list = false;

    // Variavel auxiliar para gerar as listas
    GLuint aux_list = 0;

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
    int c1, c2, c3;

    // Multiplicador de ks
    float ks_mult;

    // Struct de material auxiliar
    material_t aux_material;
    float *aux_mat_vet;
    uint cont = 0;
    // Faz um map de materiais para auxiliar na utilização
    std::map<std::string, material_t>
        mat_map;

    // Vertice auxiliar
    vertex_t aux_vertex = {0};

    std::ifstream file, material_file;
    std::string header, readl, material_token, mat_header, mat_readl;
    char *aux_string = new char[200];
    glEnable(GL_TEXTURE_2D);
    // Tenta abrir o arquivo
    file.open(fname);
    if (!file.is_open())
    {
        cList.clear();
        printf("Não conseguiu abrir o arquivo [%s] \n", fname);
        return;
    }
    else
        printf("Abriu o arquivo [%s] e esta lendo \n", fname);

    while (file.peek() != EOF)
    {
        cont++;
        // Obtem o header
        std::getline(file, header, ' ');
        // printf("Header : %s \n", header.c_str());
        if (header.size() > 8)
        {
            printf("%s| Linha %d \n", header.c_str(), cont);
            // exit(1);
        }
        // Verifica o tipo de dado q está lendo
        if (header == "#") // Comentário
        {
            // Comentário só avança para a proxima linha
            std::getline(file, readl);
        }
        else if (header == "g")
        {
            std::getline(file, readl);
        }
        else if (header == "s")
        {
            std::getline(file, readl);
        }
        else if (header == "o") // Gera uma mesh
        {
            if (generating_list)
            {
                printf("Finalizou a leitura de um objeto ! \n");
                // Para de desenhar na mesma mesh e gera outra mesh
                glPopMatrix();
                glDisable(GL_TEXTURE_2D);
                glEndList();
            }
            std::getline(file, readl);

            // Gera uma nova lista
            generating_list = true;

            aux_list = glGenLists(1);

            cList.push_back(aux_list);
            printf("Gerou uma nova lista para o objeto %s [Lista = %d] \n", readl.c_str(), aux_list);
            // Começa a compilar a lista
            glNewList(aux_list, GL_COMPILE);
            glEnable(GL_TEXTURE_2D);
            glPushMatrix();
            // exit(0);
        }
        else if (header == "v") // Ponto
        {
            // Lê as coordenadas do ponto
            std::getline(file, readl);
            sscanf(readl.c_str(), "%lf %lf %lf", &v3.x, &v3.y, &v3.z);
            vec_position.push_back(v3);
        }
        else if (header == "vt") // Textura
        {
            // Lê as coordenadas de textura
            std::getline(file, readl);
            sscanf(readl.c_str(), "%lf %lf", &v2.x, &v2.y);
            vec_texturas.push_back(v2);
        }
        else if (header == "vn") // Normal
        {
            // Lê a coordenada de normal
            std::getline(file, readl);
            sscanf(readl.c_str(), "%lf %lf %lf", &v3.x, &v3.y, &v3.z);
            vec_normal.push_back(v3);
        }
        else if (header == "mtllib")
        {
            // Lê o nome do arquivo
            std::getline(file, readl);
            strcpy(aux_string, "assets/models/");
            strcat(aux_string, readl.c_str());
            material_file.open(aux_string);

            if (!material_file.is_open())
            {
                printf("Model::Loader::Nao conseguiu abrir o arquivo de materiais [%s]\n ", aux_string);
                exit(1);
            }

            while (material_file.peek() != EOF)
            {
                mat_header.clear();
                std::getline(material_file, mat_header, ' ');

                if (mat_header == "#")
                {
                    std::getline(material_file, readl);
                }
                else if (mat_header == "Ni")
                {
                    // Nao usa entao ignora
                    std::getline(material_file, readl);
                }
                else if (mat_header == "d")
                {
                    // Nao usa entao ignora
                    std::getline(material_file, readl);
                }
                else if (mat_header == "illum")
                {
                    // Nao usa entao ignora
                    std::getline(material_file, readl);
                }
                else if (mat_header.find("newmtl") != mat_header.npos)
                {
                    // Lê a string de material
                    std::getline(material_file, material_token);

                    // Cria uma struct de material com essa key no map
                    aux_material = mat_map[material_token];
                }
                else if (mat_header[0] == 'K')
                {
                    // Lê a componente e salva no respectivo vetor
                    std::getline(material_file, readl);
                    sscanf(readl.c_str(), "%lf %lf %lf", &v3.x, &v3.y, &v3.z);

                    aux_material = mat_map[material_token];

                    if (mat_header[1] == 'a')
                    {
                        aux_mat_vet = aux_material.ambient;
                    }
                    else if (mat_header[1] == 'd')
                    {
                        aux_mat_vet = aux_material.diffuse;
                    }
                    else if (mat_header[1] == 's')
                    {
                        aux_mat_vet = aux_material.specular;
                    }
                    else if (mat_header[1] == 'e')
                    {
                        // Nao faco ideia do q seja 'e', mas n usamos, entao nao importa
                        aux_mat_vet = NULL;
                    }

                    if (aux_mat_vet != NULL)
                    {
                        aux_mat_vet[0] = v3.x;
                        aux_mat_vet[1] = v3.y;
                        aux_mat_vet[2] = v3.z;
                        aux_mat_vet[3] = 1;
                    }
                }
                else if (mat_header == "Ns")
                {
                    // Lê o valor de shinines e armazena ele no vetor do material
                    std::getline(material_file, readl);
                    sscanf(readl.c_str(), "%f", &ks_mult);
                    mat_map[material_token].shine[0] = aux_material.shine[1] = aux_material.shine[2] = ks_mult;
                    mat_map[material_token].shine[3] = 1.0f;
                }
                else if (mat_header == "map_Kd") // Textura
                {
                    std::getline(material_file, readl);
                    // Carrega a textura em um vetor de texturas
                    GLuint idTextura = SOIL_load_OGL_texture(readl.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_DDS_LOAD_DIRECT | SOIL_FLAG_INVERT_Y);
                    printf("Model::Loader::SOIL::%s \n", SOIL_last_result());
                    mat_map[material_token].texture = idTextura;
                    this->loaded_textures.push_back(idTextura);
                }
            }
            material_file.close();
            printf("Model::Loader::Leu o arquivo de material!\n");
            // exit(1);
            std::map<std::string, material_t>::iterator it;

            for (it = mat_map.begin(); it != mat_map.end(); it++)
            {
                printf("[%s] ", it->first.c_str());
            }
            printf("\n");
            // exit(1);
        }
        else if (header == "usemtl") // Usa o material apropriado para o vértice
        {
            // Pega qual material deve renderizar
            std::getline(file, readl);

            // Procura o material no map
            aux_material = mat_map[readl];
            printf("Model::Loader::Usando material [%s] \n ", readl.c_str());
            printf("Model::Loader::Usando a textura =  [%d] \n ", aux_material.texture);

            // Usa a textura, se houver
            if (aux_material.texture)
                glBindTexture(GL_TEXTURE_2D, aux_material.texture);
            else
                printf("Model::Loader::Material nao tem textura !\n");

            // Muda o material do Body de acordo com os parametros da textura
            glMaterialfv(GL_FRONT, GL_AMBIENT, aux_material.ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, aux_material.diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, aux_material.specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, aux_material.shine);
        }
        else if (header == "f") // Linha de face
        {
            // Lê uma face e renderiza ela

            // Posicao - Textura - Normal
            std::getline(file, readl);
            // printf("%s \n", readl.c_str());
            glBegin(GL_TRIANGLE_FAN);
            for (int i = 0, aux_read = 4; readl[i] != '\0' && i < readl.size() && aux_read; i++)
            {

                aux_read = sscanf(readl.c_str() + i, "%d/%d/%d", &c1, &c2, &c3);

                // printf("%d %d %d\n ", c1, c2, c3);
                // Pega os indexs e coloca nos vetores
                index_position.push_back(c1);
                index_tex.push_back(c2);
                index_normal.push_back(c3);

                // Indexa o vértice
                // Subtrai 1 porque os vértices começam em 1 em .obj
                aux_vertex.point = vec_position[c1 - 1];
                aux_vertex.tex_cord = vec_texturas[c2 - 1];
                aux_vertex.normal = vec_normal[c3 - 1];

                // Mudas as coordenadas de textura
                glTexCoord2d(aux_vertex.tex_cord.x, aux_vertex.tex_cord.y);

                // Muda o vetor normal
                glNormal3d(aux_vertex.normal.x, aux_vertex.normal.y, aux_vertex.normal.z);

                // Renderiza o vértice
                glVertex3d(aux_vertex.point.x, aux_vertex.point.y, aux_vertex.point.z);

                while (readl[i] != ' ' && readl[i] != '\0')
                {
                    i++;
                }
            }
            glEnd();
            // exit(1);
        }
    }
    if (generating_list)
    {
        // Para de desenhar na mesma mesh e gera outra mesh
        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        glEndList();
    }

    printf("Model::Loader::Terminou de Carregar o objeto\n");

    // Fecha os arquivos e libera a memoria
    file.close();
    delete aux_string;
}

// Função para rotacionar o modelo
void Model::rotateModel(vec3f_t *rot)
{
    printf("%f %f %f \n",rot->x,rot->y,rot->z);
    this->rot_vec.x = rot->x;
    this->rot_vec.y = rot->y;
    this->rot_vec.z = rot->z;
}

// Função para transladar o modelo
void Model::moveModel(vec3f_t *mov)
{
    this->origin.x = mov->x;
    this->origin.y = mov->y;
    this->origin.z = mov->z;
}

void Model::scaleModel(vec3f_t *scale_vec)
{
    this->scale.x = scale_vec->x;
    this->scale.y = scale_vec->y;
    this->scale.z = scale_vec->z;
}

void Model::renderModel()
{
    glPushMatrix();

    glTranslated(origin.x, origin.y, origin.z);

    // Rotaçao em x,y,z
    glRotated(rot_vec.x, 1, 0, 0);
    glRotated(rot_vec.y, 0, 1, 0);
    glRotated(rot_vec.z, 0, 0, 1);

    glScalef(scale.x, scale.y, scale.z);
    // Carrega todas as listas de exibição
    // glCallLists(this->cList.size(), GL_UNSIGNED_INT, this->cList.data());
    for (int i = 0; i < this->cList.size(); i++)
    {
        glCallList(cList[i]);
    }
    glPopMatrix();
}

Model::Model()
{
    this->origin = {0};
    this->rot_vec = {0};
    this->scale = {
        .x = 1.0f,
        .y = 1.0f,
        .z = 1.0f};
}

Model::~Model()
{
    // Libera toda a memoria utilizada pelo modelo
    if (this->loaded_textures.size())
    {
        // Deleta todas as texturas que o objeto utilizava
        glDeleteTextures(this->loaded_textures.size(), this->loaded_textures.data());
    }
    for (int i = 0; i < this->cList.size(); i++)
    {
        // Deleta as listas de exibicao
        glDeleteLists(this->cList.at(i), 1);
    }
}
