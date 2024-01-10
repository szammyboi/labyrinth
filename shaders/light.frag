#version 460 core
out vec4 FragColor;

in vec3 Normal;

uniform vec3 lightColor;

void main()
{
    FragColor = vec4(lightColor, 1.0);
} 