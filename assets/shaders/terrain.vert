#version 460 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_tex_coord;

uniform mat4 projection, view, model;
uniform sampler2D heightmap;
// uniform float height_scale;

out vec2 tex_coord;

void main() {
    tex_coord = vertex_tex_coord;

    // float height = texture(heightmap, vertex_tex_coord).r * height_scale;
    float height = texture(heightmap, vertex_tex_coord).r * 2.0;
    vec3 displaced = vertex_position + vec3(0.0, height, 0.0);

    gl_Position = projection * view * model * vec4(displaced, 1.0);
}