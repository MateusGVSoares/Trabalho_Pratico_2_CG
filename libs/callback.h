#ifndef __CALLBACK__
#define __CALLBACK__

#include <GL/glut.h>

typedef struct Key
{
    int w;
    int a;
    int s;
    int d;
    int up;
    int down;
    int left;
    int right;
    int space;
    int enter;
    int z;
    int x;
    int c;
    int v;
    int b;
    int n;
} keyboard_t;

extern keyboard_t keyboard;

// Aspect Ratio
// MAX_X
// MAX_Y
extern float razaoAspecto, prev_wh, prev_ww, max_x, max_y;

extern GLuint x_mouse, y_mouse;

void keyboardFct(unsigned char key, int x, int y);
void reshapeFct(int width, int height);
void keyboardSpecial(int key, int x, int y);
void onMousePassiveMovement(int x, int y);
#endif