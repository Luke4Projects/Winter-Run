#include "include/game.h"
#include "include/shader.h"
#include "include/input.h"
#include <ctime>
#include <windows.h> // this is just for the playsound() function

Game game; // this is defined in game.h

int main() {

    // Initialize the game
    if(game.init() == -1) {
        return -1;
    }

    // generate random seed
    srand((unsigned int)time(NULL));

    // load textures // TODO put this somewhere else
    unsigned int treeTexture = createTexture("assets//img/tree.png", true);
    game.textures.push_back(treeTexture);
    unsigned int floorTexture = createTexture("assets//img/floor.png", false);
    game.textures.push_back(floorTexture);

    // create first obstacle
    float x = -5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(10+5)));
    Entity tree(glm::vec3(x, 0.5f, game.camera.pos.z-3), glm::vec3(1.0f, 4.f, 1.0f), game.textures[0]);
    game.obstacles.push_back(tree);

    // delta time variables
    float lastCalledTime = (float)glfwGetTime();

    // Play the theme song, and loop it
    PlaySound(TEXT("assets//sfx/song.wav"), NULL, SND_ASYNC | SND_LOOP);

    // The main game loop
    while(!glfwWindowShouldClose(game.window)) {

        // get delta time
        float currentFrame = (float)glfwGetTime();
        game.deltaTime = currentFrame - lastCalledTime;
        lastCalledTime = currentFrame;

        // get mouse position
        glfwGetCursorPos(game.window, &game.mouseX, &game.mouseY);

        // user input
        keyboardInput();

        // render the game
        game.render();

        // poll events and swap buffers
        glfwSwapBuffers(game.window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}
