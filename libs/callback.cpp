#include "callback.h"
#include <iostream>

float razaoAspecto = 16.0f / 9.0f, prev_wh, prev_ww;
float max_x = 0, max_y = 0;

GLuint x_mouse = 0, y_mouse = 0;

keyboard_t keyboard = {0};

// Callback para pressionamento do teclado
void keyboardFct(unsigned char key, int x, int y)
{
#ifdef DEBUG
    printf("Keyboard Callback [%s] : Key [%c] | Mouse_Pos [%d][%d]\n", __func__, key, x, y);
#endif

    switch (key)
    {

    case 13:
        if (keyboard.enter)
            keyboard.enter = 0;
        else
            keyboard.enter = 1;
        break;

    case 'w':
    case 'W':
        if (keyboard.w)
            keyboard.w = 0;
        else
            keyboard.w = 1;
        break;
    case 'a':
    case 'A':
        if (keyboard.a == 1)
            keyboard.a = 0;
        else
            keyboard.a = 1;
        break;
    case 's':
    case 'S':
        if (keyboard.s)
            keyboard.s = 0;
        else
            keyboard.s = 1;
        break;
    case 'd':
    case 'D':
        if (keyboard.d)
            keyboard.d = 0;
        else
            keyboard.d = 1;
        break;
    case ' ':
        if (keyboard.space)
            keyboard.space = 0;
        else
            keyboard.space = 1;
        break;

    case 'z':
    case 'Z':
        if (keyboard.z)
        {
            keyboard.z = 0;
        }
        else
            keyboard.z = 1;
        break;
    case 'x':
    case 'X':
        if (keyboard.x)
            keyboard.x = 0;
        else
            keyboard.x = 1;
        break;

    case 'c':
    case 'C':
        if (keyboard.c)
            keyboard.c = 0;
        else
            keyboard.c = 1;
        break;
    case 'v':
    case 'V':
        if (keyboard.v)
            keyboard.v = 0;
        else
            keyboard.v = 1;
        break;
    case 'b':
    case 'B':
        if (keyboard.b)
            keyboard.b = 0;
        else
            keyboard.b = 1;
        break;
    case 'n':
    case 'N':
        if (keyboard.n)
            keyboard.n = 0;
        else
            keyboard.n = 1;
        break;
     case 'l':
    case 'L':
        if (keyboard.l)
            keyboard.l = 0;
        else
            keyboard.l = 1;
        break;
    }

}

void onMousePassiveMovement(int x , int y)
{
    x_mouse = x;
    y_mouse = y;
    // Recentraliza o ponteiro do mouse
    // glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
}

// Callback para pressionamento de Teclas Especiais
void keyboardSpecial(int key, int x, int y)
{
#ifdef DEBUG
    printf("Keyboard Callback [%s] : Key [%c] | Mouse_Pos [%d][%d]\n", __func__, key, x, y);
#endif

    switch (key)
    {
    case GLUT_KEY_UP:
        if (keyboard.up)
            keyboard.up = 0;
        else
            keyboard.up = 1;
        break;
    case GLUT_KEY_DOWN:
        if (keyboard.down)
            keyboard.down = 0;
        else
            keyboard.down = 1;
        break;
    case GLUT_KEY_LEFT:
        if (keyboard.left)
            keyboard.left = 0;
        else
            keyboard.left = 1;
        break;
    case GLUT_KEY_RIGHT:
        if (keyboard.right)
            keyboard.right = 0;
        else
            keyboard.right = 1;
        break;
    }
}

static bool reshaping = 0;

// Callback para redimensionamento
void reshapeFct(int width, int height)
{
    // #ifdef DEBUG
    printf("Reshape Callback [%s] : Width [%d] | Height [%d] \n", __func__, width, height);
    // #endif

    if (width != prev_ww)
    {
        prev_ww = width;
        if (((float)width / (float)height) != razaoAspecto && !reshaping)
        {
            reshaping = 1;
            glutReshapeWindow(width, (int)(width * (1 / razaoAspecto)));
        }
        else
            reshaping = 0;
    }
    else if (height != prev_wh)
    {
        prev_wh = height;
        if (((float)width / (float)height) != razaoAspecto && !reshaping)
        {
            reshaping = 1;
            glutReshapeWindow((int)(height * razaoAspecto), height);
        }
        else
            reshaping = 0;
    }
    // Redimensiona o desenho do open_gl
    // razaoAspecto = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    max_x = 256 * razaoAspecto;
    max_y = 224;

    glFrustum(-razaoAspecto, razaoAspecto, -1, 1, 1, 3800);
    // glOrtho(-max_x, max_x, -max_y, max_y, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}