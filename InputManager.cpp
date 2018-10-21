#include "InputManager.h"

InputManager::InputManager()
{
}
InputManager::~InputManager()
{
}

void InputManager::keyPressed(unsigned int keyID)
{
    _keyMap[keyID] = true;
}

void InputManager::keyReleased(unsigned int keyID)
{
    _keyMap[keyID] = false;
}

bool InputManager::isKeyDown(unsigned int keyID)
{
    auto it = _keyMap.find(keyID);
	if (it != _keyMap.end())
		return it->second;
	else
		return false;
}