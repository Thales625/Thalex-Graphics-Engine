#version 460 core

out vec4 FragColor;

in vec3 normal;
in vec2 tex_coord;

uniform vec3 color;
uniform vec3 sun_dir;

void main()
{
    // normalize
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(sun_dir);

    // light intensity
    float diff = max(dot(norm, light_dir), 0.1);

    // color
    FragColor = vec4(color * diff, 1.0);
}