#ifndef POINT_LIGHT
#define POINT_LIGHT

#include "Light.h"

class PointLight : public Light {
public:
    PointLight(glm::vec3& pos, glm::vec3& col, float strength, glm::vec3& attenuation);
    PointLight();
    ~PointLight();

    float getConstant() {return _constant;}
    float getLinear() {return _linear;}
    float getQuadratic() {return _quadratic;}

private:
    float _constant;
    float _linear;
    float _quadratic;
};


#endif