#version 330 core

layout(location=0) in vec4 vertex;

out vec2 fragmentUV;

uniform mat4 projectionMatrix;
uniform mat4 transformMatrix;

void main()
{
    gl_Position = projectionMatrix * transformMatrix * vec4(vertex.xy, 0.0, 1.0);
    // gl_Position = projectionMatrix * vec4(vertex.xy, 0.0, 1.0);
    fragmentUV = vec2((vertex.x+1.0)/2.0, (-vertex.y+1.0)/2.0);
}