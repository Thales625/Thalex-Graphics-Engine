#version 460 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_tex_coord;
layout(location = 2) in vec3 vertex_normal;

uniform mat4 projection, view, model;

out vec3 normal;

void main()
{
    normal = mat3(transpose(inverse(model))) * vertex_normal;
    gl_Position = projection * view * model * vec4(vertex_position, 1.0);
}