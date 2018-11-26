#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include <unordered_map>

class InputManager {
public:
    InputManager();
    ~InputManager();

    void update();

    void keyPressed(unsigned int keyID);
    void keyReleased(unsigned int keyID);
    bool isKeyDown(unsigned int keyID);

    int getMouseX() { return _mouseX; }
    int getMouseY() { return _mouseY; }
    void setMouseCoords(int x, int y);

private:
    std::unordered_map<unsigned int, bool> _keyMap;
    int _mouseX, _mouseY;
};

#endif