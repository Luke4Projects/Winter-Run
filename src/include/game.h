#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "entity.h"
#include "camera.h"
#include "particle.h"
#include "text_renderer.h"

enum GameStates {
    MAIN_MENU,
    PLAYING,
    DEAD
};

class Game {
public:
    GLFWwindow* window;
    float windowWidth,windowHeight;
    unsigned int shader,colorShader,VAO;
    float FOV;
    std::vector<unsigned int> textures;
    std::vector<Entity> obstacles;
    std::vector<Particle> particles;
    Camera camera;
    float floorZ;
    float deltaTime;
    TextRenderer* textRenderer;
    int currentGameState;
    double mouseX,mouseY;
    bool mouseDown;
    int score;
    
    int init();
    void render();
    void renderMainMenu();
    void renderDeadMenu();
};

extern Game game; // the global game variable, declared in main.cpp

#endif