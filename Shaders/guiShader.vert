#version 330 core

layout(location=0) in vec2 vertexPosition;

out vec2 textureCoords;

uniform mat4 transformMatrix;

void main()
{
    gl_Position = transformMatrix * vec4(vertexPosition, 0.0, 1.0);
    textureCoords = vec2((vertexPosition.x+1.0)/2.0, (vertexPosition.y+1.0)/2.0);
    textureCoords.y *= -1.0;
}