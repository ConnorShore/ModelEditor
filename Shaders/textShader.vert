#version 330 core

layout(location=0) in vec4 vertex;

out vec2 fragmentUV;

uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * vec4(vertex.xy, 0.0, 1.0);
    fragmentUV = vec2(vertex.zw);
}