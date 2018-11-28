#include "Button.h"
#include "Loader.h"

Button::Button(GUI* parent, float x, float y, float sx, float sy, std::string& textureFile, bool relativePos)
     : GUI(parent,x,y,sx,sy,textureFile,relativePos)
{
    _type = GUI_BUTTON;
    _enabled = true;
}

Button::Button(float x, float y, float sx, float sy, std::string& textureFile) : GUI(x,y,sx,sy,textureFile)
{
    _type = GUI_BUTTON;
    _enabled = true;
}

Button::Button() : GUI()
{
    _type = GUI_BUTTON;
    _enabled = true;
}

Button::~Button()
{
}

void Button::update()
{
    
}

void Button::onClick()
{
    if(_enabled) {
        if(eventCallback != nullptr) {
            eventCallback();
        }
    }
}