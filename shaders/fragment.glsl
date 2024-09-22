#version 460 core

out vec4 FragColor;

in vec3 normal;
//in vec2 tex_coord;

uniform vec3 color;
uniform vec3 sun_dir;

//uniform sampler2D texture1;

void main()
{
    FragColor = vec4(color * dot(normal, sun_dir), 1.0);
    //FragColor = texture(texture1, tex_coord);
}