#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>

class Camera {
public:
    Camera() {}
    ~Camera() {}

    void init(int screenWidth, int screenHeight);

    glm::mat4 createProjectionMatrix();
    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();

    glm::vec3 getPosition() { return _position; }

    void setPosition(float x, float y, float z) { _position = glm::vec3(x,y,z); }

private:
    int _screenWidth, _screenHeight;
    float _fov;
    float _zNear, _zFar;

    glm::vec3 _position, _direction, _up;
    glm::mat4 _projectionMatrix;
};

#endif