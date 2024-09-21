#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal_out;

void main()
{
    normal_out = normal;
    gl_Position = projection * view * model * vec4(position, 1.0);
}