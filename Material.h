#ifndef MATERIAL 
#define MATERIAL

#include "glm/glm.hpp"

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    Material(glm::vec3& ambient, glm::vec3& diffuse, glm::vec3& specular, float shininess)
    {
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->shininess = shininess;
    }

    Material()
    {
        this->ambient = glm::vec3(0.5f);
        this->diffuse = glm::vec3(0.5f);
        this->specular = glm::vec3(0.5f);
        this->shininess = 0.2f;
    }
};

#endif