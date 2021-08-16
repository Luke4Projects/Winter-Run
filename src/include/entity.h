#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>

class Entity {
public:
    glm::vec3 pos,scale;
    unsigned int texture;
    bool usedToSpawn;
    Entity(glm::vec3 pos, glm::vec3 scale, unsigned int texture);
    void render(unsigned int VAO, unsigned int shader);
    void collideWithCamera();
};

void createEntities();

#endif