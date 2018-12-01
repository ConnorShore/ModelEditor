#version 330 core

layout(location=0) in vec2 vertex;

out vec2 fragmentUV;

uniform mat4 projectionMatrix;
uniform mat4 transformMatrix;

void main()
{
    gl_Position = projectionMatrix * transformMatrix * vec4(vertex, 0.0, 1.0);
    fragmentUV = vec2((vertex.x+1.0)/2.0, (vertex.y+1.0)/2.0);
}