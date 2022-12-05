#include "Camera.h"
#include <iostream>

Camera::Camera(vec3f_t origin, double sense)
{
    // Todos definidos de 0 a 360
    this->pitch = 0;
    this->yaw = 0;
    this->roll = 0;
    this->sense = sense;
    this->direction = {0};
    this->origin = origin;
}

void Camera::updateCamera()
{
    // DETALHE
    // Faça o produto vetorial do vetor que aponta para cima com o vetor que aponta para a direção para obter um vetor paralelo à esquerda
    // Faça o produto vetorial do vetor que aponta para direção com o vetor que aponta para cima para obter um vetor paralelo à direita

    // Câmera não faz rotação em torno do eixo Y, entao calculamos roll e pitch
    vec3f_t mouse_pointer = {0};

    int w = glutGet(GLUT_WINDOW_WIDTH), h = glutGet(GLUT_WINDOW_HEIGHT);

    mouse_pointer.x = (float)x_mouse / w - 0.5;
    mouse_pointer.y = (float)y_mouse / h - 0.5;

    // printf("Mouse vector : %f %f\n", mouse_pointer.x, mouse_pointer.y);
    yaw += mouse_pointer.x * sense;
    pitch -= mouse_pointer.y * sense;

    if (pitch > 80)
    {
        pitch = 80;
    }
    else if (pitch < -80)
    {
        pitch = -80;
    }

    // Obtem um vetor unitário,
    // com base em coordenadas esféricas para a direção que está sendo olhada na camêra
    direction.x = cos(yaw) * cos(pitch);
    direction.y = sin(pitch);
    direction.z = sin(yaw) * cos(pitch);

    this->origin.x += (keyboard.w - keyboard.s) * direction.x;
    this->origin.y += (keyboard.w - keyboard.s) * direction.y;
    this->origin.z += (keyboard.w - keyboard.s) * direction.z;
    // glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH)/2,glutGet(GLUT_WINDOW_HEIGHT)/2);
}

void Camera::use()
{
    gluLookAt(origin.x, origin.y, origin.z,
              origin.x + direction.x, direction.y + origin.y, direction.z + origin.z,
              0, 1, 0);
}