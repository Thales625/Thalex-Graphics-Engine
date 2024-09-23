#version 460 core

out vec4 FragColor;

in vec3 normal;
in vec2 tex_coord;

uniform vec3 color;
uniform vec3 sun_dir;

uniform sampler2D texture1;

void main()
{
    // normalize
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(sun_dir);

    // light intensity
    float diff = max(dot(norm, light_dir), 0.2);

    // texture color
    vec4 texColor = texture(texture1, tex_coord) + vec4(color.rgb, 0);

    vec3 result = texColor.rgb * diff;

    FragColor = vec4(result, texColor.a);
}