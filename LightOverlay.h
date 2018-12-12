#ifndef LIGHT_OVERLAY
#define LIGHT_OVERLAY

#include "Light.h"
#include "Camera.h"
#include "Texture.h"
#include "LightOverlayShader.h"

class LightOverlay {
public:
    LightOverlay(Light* parent);
    ~LightOverlay();

    void update(Camera* camera);
    void render();

    glm::vec3 getPosition() {return _position;}
    glm::vec3 getNormal() {return _normal;}
    glm::vec3 getScale() {return _scale;}

private:
    Light* _parent;
    GLuint _vaoID, _vboID;
    glm::vec3 _position, _normal, _scale;
    Texture _texture;
    
    // float _vertices[15] = {
    //     -1,-1,1,      0,0,
    //     1,-1,1,      1,0,
    //     1,1,1,       1,1
    // };
    float _vertices[9] = {
        -1,-1,0,
        1,-1,0,
        1,1,0
    };
};

#endif