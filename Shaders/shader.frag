#version 330 core

#define MAX_LIGHTS 4

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float intensity;
};

struct PointLight {
    vec3 position;
    vec3 color;
    vec3 intensity;

    float constant;
    float linear;
    float quadratic;
};

in vec3 fragmentPosition;
in vec3 fragmentNormal;

out vec4 outColor;

uniform Material material;
uniform DirectionalLight directionLight;
uniform PointLight pointLights[MAX_LIGHTS];

uniform vec3 viewPosition;

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    //diffuse
    vec3 lightDirection = normalize(-light.direction);
    float dotRes = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = light.color * (dotRes * material.diffuse);

    //specular
    vec3 reflectDir = reflect(-lightDirection, normal);
    float specularFactor = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.color * specularFactor * material.specular;

    vec3 result = light.intensity * (diffuse + specular);

    return result;
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 viewDir)
{
    vec3 ambient = light.intensity * material.ambient;

    //diffuse
    vec3 toLightVec = normalize(light.position - fragmentPosition);
    float dotRes = max(dot(normal, toLightVec), 0.0);
    vec3 diffuse = light.color * (dotRes * material.diffuse);

    //attenuation
    float dist = length(light.position - fragmentPosition);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

    //specular
    vec3 reflectDir = reflect(-toLightVec, normal);
    float specularFactor = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.color * specularFactor * material.specular;

    vec3 result = attenuation * (ambient + diffuse + specular);

    return result;
}

void main()
{
    float globalAmbient = 0.1;
    vec3 normal = normalize(fragmentNormal);
    vec3 viewDir = normalize(viewPosition - fragmentPosition);

    vec3 result = vec3(globalAmbient * material.ambient);

    if(directionLight.direction.x != 0.0)
        result += calculateDirectionalLight(directionLight, normal, viewDir);

    for(int i = 0; i < MAX_LIGHTS; i++) {
            
        result += calculatePointLight(pointLights[i], normal, viewDir);
    }

    outColor = vec4(result, 1.0);
}