#version 330 core

uniform int axisID;

out vec4 outColor;

void main()
{
    vec4 result;
    if(axisID == 0)
        result = vec4(1,0,0,1);
    else if(axisID == 1)
        result = vec4(0,1,0,1);
    else if(axisID == 2)
        result = vec4(0,0,1,1);
    else
        result = vec4(1,1,1,1);
    
    outColor = result;
}