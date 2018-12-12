#version 330 core

layout(location = 0) in vec3 vertexPosition;
// layout(location = 1) in vec2 vertexUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 cameraDirection;

// out vec2 fragmentUV;

void main()
{
    mat4 mvp = projection * view * model;
    gl_Position = mvp * vec4(vertexPosition, 1.0);

    // fragmentUV = vertexUV;
}