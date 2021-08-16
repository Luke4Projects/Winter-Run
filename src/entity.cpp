#include <glad/glad.h>
#include "include/entity.h"
#include "include/game.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// --------------
// Constructor 
// --------------
Entity::Entity(glm::vec3 pos, glm::vec3 scale, unsigned int texture) {
    this->pos = pos;
    this->scale = scale;
    this->texture = texture;
    this->usedToSpawn = false;
}

// -----------------------------------------------
// Draw the current entity, and also transform it
// -----------------------------------------------
void Entity::render(unsigned int VAO, unsigned int shader) {
    // translate the model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, this->pos);
    model = glm::scale(model, this->scale);
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    
    // Draw the test model
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

// -------------------------------------------------------------------------------------------------------
// Check collision with the entity and the game camera, and if they collide send the player to game over
// -------------------------------------------------------------------------------------------------------
void Entity::collideWithCamera() {

    float x = game.camera.pos.x;
    float z = game.camera.pos.z;

    if(x > this->pos.x-this->scale.x/4 && x < this->pos.x + this->scale.x/4) {
        if(z > this->pos.z-this->scale.z/4 && z < this->pos.z + this->scale.z/4) {
            game.currentGameState = DEAD;
        }
    }

}

// ------------------------------------------------------------------------------------------------
// This creates the entities. This should be called every frame as it has the condition to detemine
// whether the entity should be created
// ------------------------------------------------------------------------------------------------
void createEntities() {
    if(game.camera.pos.z <= game.obstacles[0].pos.z && !game.obstacles[0].usedToSpawn) {
        game.obstacles[0].usedToSpawn = true;
        for(int i = 5; i < 10; i++) {
            float x = -5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(5+5)));
            Entity tree(glm::vec3(x, 0.5f, game.camera.pos.z-i), glm::vec3(1.0f, 4.f, 1.0f), game.textures[0]);
            game.obstacles.push_back(tree);
        }
    }
}