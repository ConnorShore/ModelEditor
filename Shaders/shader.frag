#version 330 core

in vec3 fragmentPosition;
in vec3 fragmentNormal;
in vec4 fragmentColor;

out vec4 outColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;

void main()
{
    float ambient = 0.2;
    vec3 normal = normalize(fragmentNormal);
    vec3 toLightVec = normalize(lightPosition - fragmentPosition);

    float dotRes = max(dot(toLightVec, normal), 0.0);

    vec3 diffuse = dotRes * lightColor;

    vec3 finalLight = ambient + diffuse;
    vec4 result = vec4(finalLight, 1.0) * fragmentColor;

    outColor = result;
}