#include "GUILabel.h"

GUILabel::GUILabel(GUI* parent, const char* text, float size, glm::vec4 color)
{
    _parent = parent;
    _text = text;
    _size = size * SCALE_FACTOR;
    _color = color;
}

GUILabel::GUILabel()
{
    _parent = nullptr;
    _text = "";
    _size = SCALE_FACTOR;
    _color = glm::vec4(1.0f);
}

GUILabel::~GUILabel()
{
}

void GUILabel::render(TextRenderer& renderer, TextShader* shader, int width, int height)
{
    glm::vec2 textSize = renderer.getStringSize(_text, _size);
    glm::vec2 pos = toPixelCoords(_parent->getOrigin(), width, height);

    pos -= textSize/2.0f;

    renderer.renderText(shader, _text, pos.x, pos.y, _size, _color);
}

glm::vec2 GUILabel::toPixelCoords(glm::vec2 coords, int width, int height)
{
    float fwidth = width * 1.0f;
    float fheight = height * 1.0f;

    glm::vec2 newCoords;

    if(coords.x < 0) {
        newCoords.x = (coords.x * fwidth) + fwidth;
    }
    else if(coords.x == 0) {
        newCoords.x = fwidth/2.0f;
    }
    else {
        newCoords.x = (coords.x * fwidth);
    }

    if(coords.y < 0) {
        newCoords.y = (coords.y * fheight) + fheight;
    }
    else if(coords.y == 0) {
        newCoords.y = fheight/2.0f;
    }
    else {
        newCoords.y = (coords.y * fheight);
    }

    return newCoords;
}