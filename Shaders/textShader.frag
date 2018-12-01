#version 330 core

in vec2 fragmentUV;

out vec4 outColor;

uniform sampler2D text;
uniform vec3 glyphColor;

void main()
{
    vec4 sampled = vec4(1.0,1.0,1.0,texture(text,fragmentUV).r);
    outColor = sampled * vec4(glyphColor, 1.0);
}