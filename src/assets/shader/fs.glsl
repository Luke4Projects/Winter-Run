#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D sample;

void main() {

    vec4 result = texture(sample, texCoord);

    if (result.a == 0.0){
        discard;
    }

    FragColor = result;
}