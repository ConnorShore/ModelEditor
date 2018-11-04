#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 color;
    vec3 specular;
    vec3 intensity;
};

in vec3 fragmentPosition;
in vec3 fragmentNormal;

out vec4 outColor;

uniform Material material;
uniform Light light;

uniform vec3 viewPosition;


void main()
{
    //float globalAmbient = 0.15;   //TODO: Add in global ambient
    vec3 ambient = light.intensity * material.ambient;

    //diffuse
    vec3 normal = normalize(fragmentNormal);
    vec3 toLightVec = normalize(light.position - fragmentPosition);
    float dotRes = max(dot(normal, toLightVec), 0.0);
    vec3 diffuse = light.color * (dotRes * material.diffuse);

    //specular
    vec3 viewDir = normalize(viewPosition - fragmentPosition);
    vec3 reflectDir = reflect(-toLightVec, normal);
    float specularFactor = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (specularFactor * material.specular);

    vec3 result = ambient + diffuse + specular;
    outColor = vec4(result, 1.0);
}