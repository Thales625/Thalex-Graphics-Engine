#version 460 core

out vec4 FragColor;
in vec3 normal_out;

uniform vec3 color;

void main()
{
    FragColor = vec4(color * dot(normal_out, vec3(0, 0, -1)), 1.0);
}