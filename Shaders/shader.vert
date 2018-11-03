#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec4 vertexColor;

out vec3 fragmentPosition;
out vec3 fragmentNormal;
out vec4 fragmentColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    mat4 mvp = projection * view * model;
    gl_Position = mvp * vec4(vertexPosition, 1.0);

    fragmentPosition = vec3(model * vec4(vertexPosition, 1.0));
    fragmentNormal = vertexNormal;
    fragmentColor = vertexColor;
}