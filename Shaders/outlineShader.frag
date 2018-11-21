#version 330 core

uniform bool isSelected;

out vec4 outColor;

void main()
{
    vec4 result;
    if(isSelected)
        result = vec4(1,0.7,0,1);
    else
        result = vec4(0,0,0,0);
    
    outColor = result;
}