#include "include/camera.h"

// -------------
// Constructor
// -------------
Camera::Camera() {
    this->pos = glm::vec3(0.0f, -0.5f, 3.0f);
    this->front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->zSpeed = 2.f;
}

// -------------------------------------------------------------
// Update the camera position and collision with invisble walls
// -------------------------------------------------------------
void Camera::update(float deltaTime) {
    this->pos.z-=this->zSpeed*deltaTime;
    this->zSpeed+=0.1f*deltaTime;

    if(this->pos.x >= 5) {
        this->pos.x = 5;
    }
    if(this->pos.x <= -5) {
        this->pos.x = -5;
    }
}