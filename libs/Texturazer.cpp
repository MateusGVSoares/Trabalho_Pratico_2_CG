// #include "Body.h"
#include "Texturazer.h"

int Texturazer::parse_script(const char *file_name)
{

    // Variáveis auxiliares
    std::ifstream *file = new std::ifstream();
    std::string input_caminho("assets/texture/");
    std::vector<vec3f_t> aux_cords;

    // float aux_vet[4] = {0};
    char *input_str = (char *)malloc(sizeof(char) * 50);

    vec3f_t aux = {0};

    int n_coordenadas,
        n_texturas;

    file->open(file_name, std::ios::in);

    // Verifica se o arquivo está aberto
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
        if (strcmp("TEXTURE_SCRIPT", input_str))
        {
            printf("FORMAT_ERROR_ON_FILE \n");
            delete input_str;
            delete file;
            return 1;
        }
    }
    else
    {
        delete input_str;
        delete file;
        return 1;
    }

    // Verifica quantos modelos de textura deve carregar
    file->getline(input_str, 30);
    sscanf(input_str, "%d", &n_texturas);

    // Carrega o vetor de modelo da textura e o vetor de texturas
    for (int i = 0; i < n_texturas; i++)
    {
        // Obtem as coordenadas do modelo
        file->getline(input_str, 30, ';');
        sscanf(input_str, "%d;", &n_coordenadas);

        for (int x = 0; x < n_coordenadas; x++)
        {
            file->getline(input_str, 30, ';');
            sscanf(input_str, "%f,%f", &aux.x, &aux.y);

            // Preenche o vetor
            aux_cords.push_back(aux);
        }

        // Append na lista de vetores de coordenadas e limpa o vetor para proxima leitura
        this->texture_cords.push_back(aux_cords);
        aux_cords.clear();

        // Lê o resto da linha para ir para a próxima
        file->getline(input_str, 50);

        // Obtem o nome do arquivo de textura
        file->getline(input_str, 100);
        // printf("nome = %s\n", input_str);

        input_caminho.append(input_str);

        // Carrega a textura usando a soil
        GLuint idTextura = SOIL_load_OGL_texture(input_caminho.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_DDS_LOAD_DIRECT);

        // Verifica se ocorreu algum erro na SOIL
        if (idTextura == 0)
        {
            printf("Erro do SOIL: '%s'\n", SOIL_last_result());
            delete input_str;
            delete file;
            return 1;
        }
        else
            this->loaded_textures.push_back(idTextura);
    }

    // Carrega as propriedades do material
    file->getline(input_str, 100);
    sscanf(input_str, "%f;%f;%f", &matDif[0], &matDif[1], &matDif[2]);
    file->getline(input_str, 100);
    sscanf(input_str, "%f;%f;%f", &matSpec[0], &matSpec[1], &matSpec[2]);
    file->getline(input_str, 100);
    sscanf(input_str, "%f;%f;%f", &matShine[0], &matShine[1], &matShine[2]);

    delete input_str;
    delete file;
    return 0;
}

// construtor
Texturazer::Texturazer(const char *script_name)
{
    memset(this->matDif, 0, sizeof(float) * 4);
    memset(this->matSpec, 0, sizeof(float) * 4);
    memset(this->matShine, 0, sizeof(float) * 4);

    this->matDif[3] = this->matSpec[3] = this->matShine[3] = 1.0f;

    // Tenta carregar a textura de acordo com o arquivo de script
    if (parse_script(script_name) == 1)
    {
        printf("Arquivo de Textura [%s] Inexistente ou Inelegivel ! \n", script_name);
    }
}
