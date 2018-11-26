#include "Button.h"
#include "Loader.h"

Button::Button(float x, float y, float sx, float sy, std::string& textureFile)
{
    _vaoID = 0;
    _vboID = 0;
    _position = glm::vec2(x,y);
    _scale = glm::vec2(sx, sy);
    _texture = Loader::loadPNG(textureFile);
    _uv = glm::vec4(0,0,1,1);
    _visible = true;

    createIDs();
}

Button::Button() : GUI()
{
}

Button::~Button()
{
}

void Button::update()
{
    
}

void Button::onClick()
{

}