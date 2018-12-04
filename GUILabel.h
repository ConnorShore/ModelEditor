#ifndef GUI_LABLE
#define GUI_LABLE

#include "GUI.h"
#include "TextRenderer.h"

#include <glm/glm.hpp>

#define SCALE_FACTOR 0.25

class GUILabel {
public:
    GUILabel(GUI* parent, const char* text, float size, glm::vec4 color);
    GUILabel();
    ~GUILabel();

    GUI* getParent() {return _parent;}
    const char* getText() {return _text;}
    float getSize() {return _size;}
    glm::vec4 getColor() {return _color;}

    void render(TextRenderer& renderer, TextShader* shader, int width, int height);

private:
    GUI* _parent;
    const char* _text;
    glm::vec4 _color;
    float _size;

    glm::vec2 toPixelCoords(glm::vec2 coords, int width, int height);
};

#endif