// STL libs
#include <bits/stdc++.h>

// OpenGL, GLUT & GLEW libs
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>

// Development libs
#include "libs/SolarSystem.h"
#include "libs/callback.h"
#include "libs/Camera.h"
#include "libs/MusicPlayer.h"
#include "libs/Model.h"

#define FONTE GLUT_BITMAP_8_BY_13

SolarSystem *sistemaSolar;
Camera *main_camera;
MusicPlayer *mainMixer;
Model *teste_model;

bool playSound = false, // Variavel de controle do som
    isPlaying = false;  // Variavel auxiliar para o som

double lightTimeout = 0.0f; // Timeout para não ficar com o pressionamento das luzes muito rápido

void printText(void *font, char *string)
{
    char *c;
    for (c = string; *c != '\0'; c++)
        glutBitmapCharacter(font, *c);
}

// Função para desenhar as informações na tela
void printInfo()
{
    glDisable(GL_LIGHTING);

    char *aux_buffer = new char[80];

    glRasterPos3f(-1.0 * razaoAspecto, 1.10, -2.0);
    sprintf(aux_buffer, " -> Iluminação Ambiente (Z/x) : %0.2f", var_amb);
    printText(FONTE, aux_buffer);

    glRasterPos3f(-1.0 * razaoAspecto, 1.00, -2.0);
    sprintf(aux_buffer, " -> Iluminação Difusa (C/v) : %0.2f", var_dif);
    printText(FONTE, aux_buffer);

    glRasterPos3f(-1.0 * razaoAspecto, 0.90, -2.0);
    sprintf(aux_buffer, " -> Iluminação Especular (B/n) : %0.2f", var_spec);
    printText(FONTE, aux_buffer);
    glRasterPos3f(-1.0 * razaoAspecto, 0.80, -2.0);
    sprintf(aux_buffer, " -> Luzes Dos Planetas : %s", lightIsOn ? "Ligada" : "Desligada");
    printText(FONTE, aux_buffer);

    delete aux_buffer;
}

void drawUpdate()
{
    // Limpa a cena e o buffer de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Carrega a identidade no sistema
    glLoadIdentity();

    // Desenha o texto na tela
    printInfo();

    // Posiciona a camera
    main_camera->use();

    // Desenha a SkyBox
    sistemaSolar->drawSkyBox();

    // Desenha todas as esferas
    sistemaSolar->updateOnDraw();

    glEnable(GL_LIGHTING);
    teste_model->renderModel();
    glDisable(GL_LIGHTING);

    // Clean Code <3
    // Swap buffers >_<
    glutSwapBuffers();
}

double calcDistance(vec3f_t *a, vec3f_t *b)
{
    vec3f_t result = {
        .x = a->x - b->x,
        .y = a->y - b->y,
        .z = a->z - b->z};

    // Calcula a distância entre os pontos
    double distance = sqrt(pow(result.x, 2) + pow(result.y, 2) + pow(result.z, 2));
    return distance;
}

void onTimeUpdate(int param)
{
    // Incrementa o contador de timeout
    lightTimeout += 1.0f / (param);

    // Limpa o estado de playSound
    playSound = 0;

    // Atualiza a posicao da camera
    main_camera->updateCamera();

    // Movimenta as esferas
    sistemaSolar->updateOnTime();

    // Verifica o pressionamento da tecla L
    if (keyboard.l && lightTimeout >= 1.0f)
    {
        lightTimeout = 0.0f;
        lightIsOn = !lightIsOn;
    }

    float distance = 0.0f;

    for (int i = 0; i < sistemaSolar->aux_sound.size(); i++)
    {
        distance = calcDistance(&main_camera->origin, sistemaSolar->aux_sound[i]);
        // verifica a distância dos pontos q deve tocar som
        if (distance <= 100.0f)
        {
            playSound = true;
            break;
        }
    }

    // Verifica se deve ou nao tocar som
    if (playSound)
    {
        // Seta o volume de acordo com a distancia, para dar o efeito de fade
        mainMixer->setVolume((100.0f - distance) / 2.0f);

        // Resume a musica
        mainMixer->resumeMusic("ambiente");
    }
    else
    {
        // Verifica se estava tocando audio
        if (mainMixer->isPlaying())
        {

            mainMixer->stopMusic();
        }
    }
    vec3f_t mov{
        .x = main_camera->origin.x + main_camera->direction.x+5*cos(main_camera->getYaw()),
        .y = main_camera->origin.y + main_camera->direction.y -5*cos(main_camera->getPitch()),
        .z = main_camera->origin.z + main_camera->direction.z +5*sin(main_camera->getYaw())};

    teste_model->moveModel(&mov);

    mov.x = +main_camera->rotation.x * 180.0f / M_PI;
    mov.y = -main_camera->rotation.y * 180.0f / M_PI;
    mov.z = +main_camera->rotation.z * 180.0f / M_PI;

    teste_model->rotateModel(&mov);
    glutPostRedisplay();
    glutTimerFunc(param, onTimeUpdate, param);
}

void configGlut()
{
    // Configura a janela da GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000 * 1 / razaoAspecto);

    glutInitWindowPosition(0, 0);
    glutCreateWindow("Solar System");

    // Configura os callbacks da GLUT
    glutDisplayFunc(drawUpdate);
    glutReshapeFunc(reshapeFct);
    glutKeyboardFunc(keyboardFct);
    glutKeyboardUpFunc(keyboardFct);
    glutSpecialFunc(keyboardSpecial);
    glutSpecialUpFunc(keyboardSpecial);
    glutPassiveMotionFunc(onMousePassiveMovement);
    glutTimerFunc(16, onTimeUpdate, 16);

    glLineWidth(8);

    prev_wh = 600 * razaoAspecto;
    prev_ww = 600;

    // Ignora repetições de teclas e verifica apenas o pressionamento e qnd soltar
    glutIgnoreKeyRepeat(1);
}

void configOpenGl()
{
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    // Não mostrar faces do lado de dentro
    // glDisable(GL_CULL_FACE);

    // Esconder o ponteiro do mouse quando dentro da janela
    glutSetCursor(GLUT_CURSOR_NONE);

    float globAmb[] = {0.15, 0.15, 0.15, 1.0};

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, false); // habilita local view
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);   // Luz ambiente global

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHT0);
}

void initGame()
{
    printf("PRECISO REVER\n SEU SORRISO UM TANTO SEM GRACA\n PRECISO VOLTAR\nMAIS UMA VEZ COM VOCE LA NA PRACA\n");
    vec3f_t cam_origin = {
        .x = 0,
        .y = 300,
        .z = -300};

    main_camera = new Camera(cam_origin, 0.004);
    sistemaSolar = new SolarSystem("solarsystem.sscp");
    mainMixer = new MusicPlayer();
    teste_model = new Model();

    // Carrega a musica
    mainMixer->loadMusic("ambiente", "assets/music/default.mp3");

    teste_model->loadModel("assets/models/sw_ship.obj");
    cam_origin.x = 150;
    cam_origin.y = 0;
    cam_origin.z = 150;

    // teste_model->moveModel(&cam_origin);
    // mainMixer->playMusic("ambiente");
}

int main(int argc, char **argv)
{
    // Inicializa a glut
    glutInit(&argc, argv);

    // Inicializa o mixer do SDL
    Mix_Init(MIX_INIT_MP3);
    SDL_Init(SDL_INIT_AUDIO);

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0)
    {
        printf("Nao conseguiu inicializar o subsistema de audio \n");
        exit(1);
    }

    // Configura a janela da glut
    configGlut();

    // Inicializa a GLEW
    glewInit();

    // Configura o OpenGl e a Iluminacao
    configOpenGl();

    // Inicializa os planetas e o mixer de audio
    initGame();

    // Começa o loop principal
    glutMainLoop();
}