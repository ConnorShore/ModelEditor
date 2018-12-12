#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>

class Camera {
public:
    Camera() {}
    ~Camera() {}

    void init(int screenWidth, int screenHeight);
    void update();

    void moveForward(float speed);
    void moveBackward(float speed);
    void moveRight(float speed);
    void moveLeft(float speed);
    void moveUp(float speed);
    void moveDown(float speed);
    void rotateUp(float speed);
    void rotateDown(float speed);
    void rotateLeft(float speed);
    void rotateRight(float speed);
    
    glm::vec3 screenToWorldCoords(float mouseX, float mouseY);
    glm::vec2 screenToNDC();

    float getPitch() { return _pitch; }
    float getYaw() { return _yaw; }
    float getRoll() { return _roll; } 
    float getSensitivity() { return _sensitivity;}

    void setPitch(float pitch) { _pitch = pitch; }
    void setYaw(float yaw) { _yaw = yaw; }
    void setRoll(float roll) { _roll = roll; }
    void setSensitivity(float sensitivity) { _sensitivity = sensitivity; }

    void setScreenDimensions(int width, int height) {_screenWidth = width; _screenHeight = height;}

    float getScreenWidth() {return _screenWidth;}
    float getScreenHeight() {return _screenHeight;}

    glm::mat4 createProjectionMatrix();
    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();

    glm::vec3 getPosition() { return _position; }
    glm::vec3 getDirection() {return _direction;}
    glm::ivec2 getMouseCoords() {return _mouseCoords;}

    void setPosition(float x, float y, float z) { _position = glm::vec3(x,y,z); }
    void setMouseCords(float x, float y) {_mouseCoords = glm::vec2(x,y);}

private:
    int _screenWidth, _screenHeight;
    float _fov;
    float _zNear, _zFar;
    float _pitch, _yaw, _roll;
    float _sensitivity;

    glm::vec3 _position, _direction, _up, _right;
    glm::mat4 _projectionMatrix;

    glm::ivec2 _mouseCoords;
};

#endif