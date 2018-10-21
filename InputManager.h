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

private:
    std::unordered_map<unsigned int, bool> _keyMap;
};

#endif