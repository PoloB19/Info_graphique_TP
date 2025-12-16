#version 330 core

// input attribute variable, given per vertex
layout(location = 0) in vec3 position;

// global matrix variables
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

// color given to the fragment shader
out vec3 fragColor;

void main() {

    //Pour qu'il soit + lumineux
    fragColor = position * vec3(5,5,5);

    gl_Position = projection * view * model * vec4(position, 1); // TODO calculate correct position
}