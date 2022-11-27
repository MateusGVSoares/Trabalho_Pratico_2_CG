#ifndef __TEXTURAZER__
#define __TEXTURAZER__

#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "vec3f.h"

class Texturazer
{
public:
    std::vector<GLuint> loaded_textures;
    std::vector<std::vector<vec3f_t>> texture_cords;
    float matDif[4];
    float matSpec[4];
    float matShine[4];
    int parse_script(const char *file_name);
    Texturazer(const char *tex_name);
};

#endif