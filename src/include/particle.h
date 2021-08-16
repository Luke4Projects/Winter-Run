#ifndef PARTICLE_H
#define PARTICLE_H

#include <glm/glm.hpp>

class Particle {
public:
    glm::vec3 pos,scale,color,speed;
    float timeAlive;
    bool shouldDie;
    Particle(glm::vec3 pos, glm::vec3 scale, glm::vec3 speed, glm::vec3 color);
    void update(float deltaTime);
    void render(unsigned int VAO, unsigned int shader);
};

#endif