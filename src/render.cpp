#include "include/game.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>

void updateProjView(float fov, float width, float height, unsigned int shader, unsigned int shader2, Camera camera); // defined below render

//
// This is caled every frame in the main game loop, and has all drawing code
//
void Game::render() {

    if(currentGameState == MAIN_MENU) {
        renderMainMenu();
    }
    if(currentGameState == DEAD) {
        renderDeadMenu();
    }

    if(currentGameState == PLAYING) {
        // update the camera
        camera.update(deltaTime);

        // create entities
        createEntities();

        // Update projection and view matrixes
        updateProjView(this->FOV, this->windowWidth, this->windowHeight, this->shader, this->colorShader, this->camera);

        // use the texture shader
        glUseProgram(shader);

        // Clear the background blue
        glClearColor(0.0745f, 0.1725f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render the floor
        if(floorZ-30 > camera.pos.z) {
            floorZ-=30.f;
        }
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0, -1.25f, floorZ-20));
        model = glm::scale(model, glm::vec3(50, 1, 50));
        model = glm::rotate(model, glm::radians(90.f), glm::vec3(1, 0, 0));
        glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // render the obstacles
        for(int i = 0; i < obstacles.size(); i++) {
            obstacles[i].render(this->VAO, this->shader);
            obstacles[i].collideWithCamera();
            // remove obstacle if it passes the camera
            if(obstacles[i].pos.z > camera.pos.z) {
                this->score++;
                obstacles.erase(obstacles.begin()+i);
            }
        }

        // create snow particles
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 4; j+=2) {
                float x = 3 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(20-3)));
                float y = 1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(5-1)));
                Particle part(glm::vec3(camera.pos.x-2.5f-(j*2.5), camera.pos.y+1.0f+(j/1.5f), camera.pos.z-1-j), glm::vec3(0.03f), glm::vec3(x, -y, -(camera.zSpeed/5)), glm::vec3(0.847, 0.89, 0.905));
                particles.push_back(part);
            }
        }

        // render the particles
        for(int i = 0; i < particles.size(); i++) {
            particles[i].update(deltaTime);
            particles[i].render(VAO, colorShader);
            if(particles[i].shouldDie) {
                particles.erase(particles.begin()+i);
            }
        }
        
        std::stringstream scoreString; scoreString<<this->score;
        this->textRenderer->RenderText("Score: "+scoreString.str(), 0, 0, 0.1f);

    }


}

//
// Sets the projection and view matrixes
// 
void updateProjView(float fov, float width, float height, unsigned int shader, unsigned int shader2, Camera camera) {

    // Update projection matrix
    glm::mat4 proj = glm::perspective(glm::radians(fov), width/height, 0.1f, 100.0f);
    glUseProgram(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader, "proj"), 1, GL_FALSE, glm::value_ptr(proj));
    glUseProgram(shader2);
    glUniformMatrix4fv(glGetUniformLocation(shader2, "proj"), 1, GL_FALSE, glm::value_ptr(proj));

    // Update view matrix
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(camera.pos, camera.pos + camera.front, camera.up);
    glUseProgram(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUseProgram(shader2);
    glUniformMatrix4fv(glGetUniformLocation(shader2, "view"), 1, GL_FALSE, glm::value_ptr(view));

}