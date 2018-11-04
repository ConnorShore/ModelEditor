#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 fragmentPosition;
in vec3 fragmentNormal;

out vec4 outColor;

uniform Material material;

uniform vec3 viewPosition;

uniform vec3 lightPosition;
uniform vec3 lightColor;

void main()
{
    //float globalAmbient = 0.15;   //TODO: Add in global ambient
    vec3 ambient = lightColor * material.ambient;

    //diffuse
    vec3 normal = normalize(fragmentNormal);
    vec3 toLightVec = normalize(lightPosition - fragmentPosition);
    float dotRes = max(dot(normal, toLightVec), 0.0);
    vec3 diffuse = lightColor * (dotRes * material.diffuse);

    //specular
    vec3 viewDir = normalize(viewPosition - fragmentPosition);
    vec3 reflectDir = reflect(-toLightVec, normal);
    float specularFactor = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightColor * (specularFactor * material.specular);

    vec3 result = ambient + diffuse + specular;
    outColor = vec4(result, 1.0);
}