#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include <unordered_map>

class InputManager {
public:
    InputManager();
    ~InputManager();

    void keyPressed(unsigned int keyID);
    void keyReleased(unsigned int keyID);
    bool isKeyDown(unsigned int keyID);

    float getMouseX() { return _mouseX; }
    float getMouseY() { return _mouseY; }
    void setMouseCoords(float x, float y);

private:
    std::unordered_map<unsigned int, bool> _keyMap;
    float _mouseX, _mouseY;
};

#endif