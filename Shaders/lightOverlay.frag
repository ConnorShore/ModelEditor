#version 330 core

// in vec2 fragmentUV;

uniform sampler2D logo;

out vec4 outColor;


void main()
{
    // vec4 result = texture(logo, fragmentUV);
    
    // outColor = result;
    outColor = vec4(1,0,0,1);
}