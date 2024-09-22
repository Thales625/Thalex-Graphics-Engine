#version 460 core

out vec4 FragColor;
in vec3 normal;

uniform vec3 color;

void main()
{
    FragColor = vec4(color * dot(normal, vec3(1, 0, 0)), 1.0);
    //FragColor = vec4(normal, 1.0);
}