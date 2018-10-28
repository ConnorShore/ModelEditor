#version 330 core

in vec4 fragmentColor;

out vec4 outColor;

uniform vec4 lightColor;

void main()
{
    vec4 result = lightColor * fragmentColor;
    outColor = result;
}