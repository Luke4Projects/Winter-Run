#ifndef SHADER_H
#define SHADER_H

#include <string>

unsigned int loadShader(std::string vertexShaderPath, std::string fragmentShaderPath);
unsigned int createTexture(char* path, bool alpha);

#endif