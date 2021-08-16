#include <glad/glad.h>
#include "include/particle.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

//
// Constructor
//
Particle::Particle(glm::vec3 pos, glm::vec3 scale, glm::vec3 speed, glm::vec3 color) {
    this->pos = pos;
    this->scale = scale;
    this->speed = speed;
    this->color = color;
    this->timeAlive = 0;
    this->shouldDie = false;
}

//
// Updates the particles variables, should be called every frame
//
void Particle::update(float deltaTime) {
    this->pos += this->speed*deltaTime;
    this->timeAlive += 1.5f*deltaTime;
    //this->scale -= 1.5f*deltaTime;
    if(this->timeAlive >= 1) {
        this->shouldDie = true;
    }
}

// ---------------------------------------------------------------------------------------------
// Draw the current particle and transform it Particles use the color shader, 
// so make sure you pass the color shader in the parameters
// ---------------------------------------------------------------------------------------------
void Particle::render(unsigned int VAO, unsigned int shader) {
    glUseProgram(shader);
    glBindVertexArray(VAO);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, this->pos);
    model = glm::scale(model, this->scale);
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform3fv(glGetUniformLocation(shader, "objColor"), 1, glm::value_ptr(this->color));
    glDrawArrays(GL_TRIANGLES, 0, 6);
}