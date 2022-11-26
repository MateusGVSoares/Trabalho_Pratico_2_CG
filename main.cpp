// STL libs
#include <bits/stdc++.h>

// OpenGL, GLUT & GLEW libs
#include <GL/glew.h>
#include <GL/freeglut.h>

// Development libs
#include "libs/SolarSystem.h"
#include "libs/callback.h"

#define FONTE GLUT_BITMAP_8_BY_13

SolarSystem *sistemaSolar;

void printText(void *font, char *string)
{
    char *c;
    for (c = string; *c != '\0'; c++)
        glutBitmapCharacter(font, *c);
}

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

    glRasterPos3f(-1.0 * razaoAspecto, 0.85, -2.0);
    sprintf(aux_buffer, " -> Iluminação Especular (B/n) : %0.2f", var_spec);
    printText(FONTE, aux_buffer);

    delete aux_buffer;
}

void drawUpdate()
{
    // Limpa a cena e o buffer de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Carrega a identidade no sistema
    glLoadIdentity();

    // Utiliza de coordenadas cilindricas para movimentar a camera
    // x = origin.x + p*sin(θ)*cos(Φ)
    // y = origin.y + p
    // z = origin.z +p*cos(θ)*cos(Φ)
    printInfo();

    gluLookAt(0, 300, -320,
              0, 0, 0,
              0, 1, 0);

    sistemaSolar->drawSkyBox();

    // Desenha todas as esferas
    sistemaSolar->updateOnDraw();

    // Clean Code <3
    // Swap buffers >_<
    glutSwapBuffers();
}

void onTimeUpdate(int param)
{
    // Movimenta as esferas
    sistemaSolar->updateOnTime();
    glutPostRedisplay();
    glutTimerFunc(param, onTimeUpdate, param);
}

void configGlut()
{
    // Configura a janela da GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(600, 600 * 1 / razaoAspecto);

    glutInitWindowPosition(0, 0);
    glutCreateWindow("Solar System");

    // Configura os callbacks da GLUT
    glutDisplayFunc(drawUpdate);
    glutReshapeFunc(reshapeFct);
    glutKeyboardFunc(keyboardFct);
    glutKeyboardUpFunc(keyboardFct);
    glutSpecialFunc(keyboardSpecial);
    glutSpecialUpFunc(keyboardSpecial);

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
    glDisable(GL_CULL_FACE);

    // Esconder o ponteiro do mouse quando dentro da janela
    // glutSetCursor(GLUT_CURSOR_NONE);

    float globAmb[] = {0.15, 0.15, 0.15, 1.0};

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, false); // habilita local view
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);   // Luz ambiente global

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHT0);
}

void initGame()
{
    sistemaSolar = new SolarSystem("solarsystem.sscp");
}

int main(int argc, char **argv)
{
    // Inicializa a glut
    glutInit(&argc, argv);

    // Configura a janela da glut
    configGlut();

    // Inicializa a GLEW
    glewInit();

    // Configura o OpenGl e a Iluminacao
    configOpenGl();

    // Inicializa os planetas
    initGame();

    // Começa o loop principal
    glutMainLoop();
}