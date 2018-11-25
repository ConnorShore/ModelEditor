#version 330 core

layout(location=0) in vec2 vertexPosition;

uniform mat4 transformMatrix;

void main()
{
    gl_Position = transformMatrix * vec4(vertexPosition, 0.0, 1.0);
}