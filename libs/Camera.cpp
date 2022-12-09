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
    this->last_x = prev_ww * razaoAspecto / 2;
    this->last_y = prev_wh / 2;
    this->rotation = {0};
}

void Camera::updateCamera()
{
    // Câmera não faz rotação em torno do eixo Y, entao calculamos roll e pitch
    vec3f_t mouse_pointer = {0};

    if (x_mouse != glutGet(GLUT_WINDOW_WIDTH) / 2 && y_mouse != glutGet(GLUT_WINDOW_HEIGHT) / 2)
    {

        float offset_x = (x_mouse - glutGet(GLUT_WINDOW_WIDTH) / 2.0);
        float offset_y = (y_mouse - glutGet(GLUT_WINDOW_HEIGHT) / 2.0);

        glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
        // printf("Mouse vector : %f %f\n", mouse_pointer.x, mouse_pointer.y);
        yaw += offset_x * sense;
        pitch -= offset_y * sense;
    }

    if (pitch > 90)
    {
        pitch = 90;
    }
    else if (pitch < -90)
    {
        pitch = -90;
    }
    rotation.x = pitch;
    rotation.y = yaw;
    rotation.z = roll;

    // Obtem um vetor unitário,
    // com base em coordenadas esféricas para a direção que está sendo olhada na camêra
    direction.x = cos(yaw) * cos(pitch);
    direction.y = sin(pitch);
    direction.z = sin(yaw) * cos(pitch);

    // Obtem um vetor unitário através do produto vetorial entre o vetor que aponta para cima e o vetor de direção
    side.x = -sin(yaw) * cos(pitch) * (keyboard.d - keyboard.a);
    side.y = 0;
    side.z = cos(yaw) * cos(pitch) * (keyboard.d - keyboard.a);

    // Para sempre ter a direção, apenas verifica se deve movimentar ou não em um vetor auxiliar
    mouse_pointer.x = (keyboard.w - keyboard.s) * direction.x;
    mouse_pointer.y = (keyboard.w - keyboard.s) * direction.y;
    mouse_pointer.z = (keyboard.w - keyboard.s) * direction.z;

    // Pega a resultante desses vetores
    this->origin.x += mouse_pointer.x + side.x;
    this->origin.y += mouse_pointer.y + side.y;
    this->origin.z += mouse_pointer.z + side.z;

    // glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH)/2,glutGet(GLUT_WINDOW_HEIGHT)/2);
}

void Camera::use()
{
    // Usa dos dados calculados para movimentar a camera
    gluLookAt(origin.x, origin.y, origin.z,
              origin.x + direction.x, direction.y + origin.y, direction.z + origin.z,
              0, 1, 0);
}