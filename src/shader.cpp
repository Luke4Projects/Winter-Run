#include "include/shader.h"
#include <fstream>
#include <iostream>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

//
// Returns a texture as an unsigned int, loaded from the path parameter
//
unsigned int createTexture(char* path, bool alpha) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    int width,height,nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if(data) {
        if(alpha) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);            
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout<<"Failed to load texture at "<<path<<std::endl;
        return NULL;
    }
    return texture;
}

//
// Returns data from a file, specified from the path parameter
//
std::string loadFile(std::string path) {

    std::ifstream inFile(path);
    std::string fileData;

    std::string line;
    while(std::getline(inFile, line)) {
        fileData += line + "\n";
    }

    return fileData;
}

//
// Create a shader program loaded from the two parameters
//
unsigned int loadShader(std::string vertexShaderPath, std::string fragmentShaderPath) {

    // Create shader source from the files
    std::string loadedVShader = loadFile(vertexShaderPath);
    std::string loadedFShader = loadFile(fragmentShaderPath);
    const char* vsource = const_cast<char*>(loadedVShader.c_str());
    const char* fsource = const_cast<char*>(loadedFShader.c_str());

    // Create vertex and fragment shaders (vs, and fs)
    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vs, 1, &vsource, NULL);
    glShaderSource(fs, 1, &fsource, NULL);
    glCompileShader(vs);
    glCompileShader(fs);

    // Check for shader compilation errors
    int  success;
    char infoLog[512];
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<infoLog<<std::endl;
    }
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fs, 512, NULL, infoLog);
        std::cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<infoLog<<std::endl;
    }

    // Create the shader program with the vertex and fragment shaders we made
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);
    glDeleteShader(vs); // we can delete shaders after adding them to the program
    glDeleteShader(fs);

    return shaderProgram;
}