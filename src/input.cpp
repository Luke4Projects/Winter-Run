#include <glad/glad.h>
#include "include/input.h"
#include "include/game.h"
#include <windows.h>

//
// This is called on window resize, it fixes the gl viewport and window width and height variables
//
void resizeEvent(GLFWwindow* window, int width, int height) {
    game.windowWidth = (float)width;
    game.windowHeight = (float)height;
    glViewport(0, 0, width, height);
}

// 
// This is called every frame and has all keyboard input code
//
void keyboardInput() {

    if(glfwGetKey(game.window, GLFW_KEY_D) == GLFW_PRESS) {
        game.camera.pos.x+=5.0f*game.deltaTime;
    }
    if(glfwGetKey(game.window, GLFW_KEY_A) == GLFW_PRESS) {
        game.camera.pos.x-=5.0f*game.deltaTime;
    }

    game.mouseDown = false;
    if(glfwGetMouseButton(game.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        game.mouseDown = true;
    }

}