#version 330 core

uniform sampler2D tex;
uniform float alpha;

in vec2 textureCoords;

out vec4 outColor;

void main()
{
    outColor = vec4(texture(tex, textureCoords).xyz, alpha);
}