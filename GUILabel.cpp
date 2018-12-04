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
    // printf("Pre Pos: %f, %f\n", _parent->getPosition().x, _parent->getPosition().y);
    glm::vec2 pos = toPixelCoords(_parent->getPosition(), width, height);
    // printf("Width: %d, Height: %d\n", width, height);
    // printf("Pos: %f, %f\n", pos.x, pos.y);
    renderer.renderText(shader, _text, pos.x, pos.y, _size, _color);
}

glm::vec2 GUILabel::toPixelCoords(glm::vec2 coords, int width, int height)
{
    float fwidth = width * 1.0f;
    float fheight = height * 1.0f;

    glm::vec2 newCoords;

    // printf("Width/2: %f\n", fwidth/2.0f);

    if(coords.x < 0) {
        // printf("in negative\n");
        newCoords.x = (coords.x * fwidth) + fwidth;
    }
    else if(coords.x == 0) {
        // printf("0");
        newCoords.x = fwidth/2.0f;
    }
    else {
        // printf("positive\n");
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