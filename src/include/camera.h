#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:    
    glm::vec3 pos,front,up;
    float zSpeed;
    Camera();
    void update(float deltaTime);
};

#endif