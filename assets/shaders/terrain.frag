#version 460 core

out vec4 FragColor;

in vec2 tex_coord;

uniform sampler2D texture_id;

void main()
{
    vec4 texColor = texture(texture_id, tex_coord);

    FragColor = texColor;
}