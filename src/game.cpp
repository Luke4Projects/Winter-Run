#include "include/game.h"
#include "include/shader.h"
#include "include/input.h"
#include <iostream>

unsigned int setVertexData();

//
// Initializes OpenGL and sets default variable values
//
int Game::init() {
    
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window
    this->window = glfwCreateWindow(1280, 720, "Winter Run", NULL, NULL);
    if(this->window == NULL) {
        std::cout<<"Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(this->window);

    // Initialize GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout<<"Failed to initialize GLAD\n";
        glfwTerminate();
        return -1;
    }

    // enable depth sorting
    glEnable(GL_DEPTH_TEST);

    // enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    // set callbacks
    glfwSetFramebufferSizeCallback(this->window, resizeEvent);

    // Set variable values
    this->windowWidth = 1280;
    this->windowHeight = 720;
    this->FOV = 100.0f;
    this->floorZ = 0.f;
    this->shader = loadShader("assets//shader/vs.glsl", "assets//shader/fs.glsl");
    this->colorShader = loadShader("assets//shader/vs.glsl", "assets//shader/color-fs.glsl");
    this->VAO = setVertexData();
    this->textRenderer = new TextRenderer((unsigned int)this->windowWidth, (unsigned int)this->windowHeight);
    this->textRenderer->Load("assets//font/arial.ttf", 700);
    this->currentGameState = MAIN_MENU;
    this->mouseDown = false;
    this->score = 0;

    glUseProgram(game.shader);
    return 0;
}

//
// Returns a vertex array object, for a plane
//
unsigned int setVertexData() {
    
    float vertices[] = {
        -0.5f, -0.5f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.0f,  1.0f, 1.0f,
    };

    unsigned int VAO,VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    return VAO;
}