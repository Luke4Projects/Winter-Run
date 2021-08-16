#include "include/game.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <windows.h>
#include <sstream>

class Button {
public:
    glm::vec3 pos;
    std::string text;
    Button(float x, float y, std::string text) {
        this->pos = glm::vec3(x,y,0);
        this->text = text;
    }
    bool checkClick() {
        double xpos = game.mouseX/(game.windowWidth - game.windowWidth/2) - 1;
        double ypos = game.mouseY/(game.windowHeight - game.windowHeight/2) - 1;
        //std::cout<<xpos<<std::endl;
        if(game.mouseDown && xpos > this->pos.x-0.25f && xpos < this->pos.x+0.25f && 
        -ypos > this->pos.y-0.15f && -ypos < this->pos.y+0.15f) {
            return true;
        }
        return false;

    }
};

Button buttons[] = {
    Button(0,0,"Play"),
    Button(0,-0.7f, "Quit")
};

// -----------------------------------------------------------------------
// This has all the code for the main menu rendering and updating
// -----------------------------------------------------------------------
void Game::renderMainMenu() {

    // Clear background
    glClearColor(0.0745f, 0.1725f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // use the color shader (no textures)
    glUseProgram(colorShader);

    // set projection and view matrixes
    glUniformMatrix4fv(glGetUniformLocation(colorShader, "proj"), 1, GL_FALSE, glm::value_ptr(glm::perspective(glm::radians(45.f), windowWidth/windowHeight, 0.1f, 100.f)));
    glUniformMatrix4fv(glGetUniformLocation(colorShader, "view"), 1, GL_FALSE, glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3))));

    // Draw buttons
    for(int i = 0; i < 2; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, buttons[i].pos);
        model = glm::scale(model, glm::vec3(1, 0.3f, 1));
        glUniformMatrix4fv(glGetUniformLocation(colorShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform3f(glGetUniformLocation(colorShader, "objColor"), 0.3176f, 0.7686f, 0.8274f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        textRenderer->RenderText(buttons[i].text, buttons[i].pos.x+0.9f, buttons[i].pos.y*0.83f-0.925f, 0.1f);
        glUseProgram(colorShader);
    }

    // check if buttons are being clicked
    if(buttons[0].checkClick()) {
        game.currentGameState = PLAYING;
    }
    if(buttons[1].checkClick()) {
        glfwSetWindowShouldClose(game.window, true);
    }

    // render the game title
    textRenderer->RenderText("Winter Run", 0.73f, -0.3f, 0.1f);

}

// -----------------------------------------------------------------------
// This has all the code for the game over screen rendering and updating
// -----------------------------------------------------------------------
void Game::renderDeadMenu() {
    // Clear background
    glClearColor(0.4f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // use the color shader (no textures)
    glUseProgram(colorShader);

    // set projection and view matrixes
    glUniformMatrix4fv(glGetUniformLocation(colorShader, "proj"), 1, GL_FALSE, glm::value_ptr(glm::perspective(glm::radians(45.f), windowWidth/windowHeight, 0.1f, 100.f)));
    glUniformMatrix4fv(glGetUniformLocation(colorShader, "view"), 1, GL_FALSE, glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3))));

    // Draw buttons
    for(int i = 0; i < 2; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, buttons[i].pos);
        model = glm::scale(model, glm::vec3(1, 0.3f, 1));
        glUniformMatrix4fv(glGetUniformLocation(colorShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform3f(glGetUniformLocation(colorShader, "objColor"), 0.3176f, 0.7686f, 0.8274f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        textRenderer->RenderText(buttons[i].text, buttons[i].pos.x+0.9f, buttons[i].pos.y*0.83f-0.925f, 0.1f);
        glUseProgram(colorShader);
    }

    // check if buttons are being clicked
    if(buttons[0].checkClick()) {
        game.currentGameState = PLAYING;
        this->floorZ = 0.f;
        this->camera.pos = glm::vec3(0.0f, -0.5f, 3.0f);
        this->camera.zSpeed = 2.f;
        this->score = 0;
        this->obstacles.clear();
        this->obstacles.push_back(Entity(glm::vec3((-5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(10+5)))), 0.5f, game.camera.pos.z-3), glm::vec3(1.0f, 4.f, 1.0f), game.textures[0]));
    }
    if(buttons[1].checkClick()) {
        glfwSetWindowShouldClose(game.window, true);
    }

    // render the game title
    textRenderer->RenderText("Game Over", 0.73f, -0.3f, 0.1f);    
    // render the score
    std::stringstream scoreString; scoreString<<this->score;
    this->textRenderer->RenderText("Score: "+scoreString.str(), 0.88f, -0.5f, 0.05f);

}