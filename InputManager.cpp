#include "InputManager.h"

#include <SDL2/SDL.h>

InputManager::InputManager()
{
}
InputManager::~InputManager()
{
}

void InputManager::update()
{
	SDL_Event evnt;
    while(SDL_PollEvent(&evnt)) {
        switch(evnt.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_MOUSEMOTION:
            //TODO: Add mouselook
                setMouseCoords(evnt.motion.x, evnt.motion.y);
                break;
            case SDL_KEYDOWN:
                keyPressed(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                keyReleased(evnt.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                keyPressed(evnt.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                keyReleased(evnt.button.button);
                break;
        }
    }
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

void InputManager::setMouseCoords(int x, int y)
{
	_mouseX = x;
	_mouseY = y;
}