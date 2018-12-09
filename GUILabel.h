#ifndef GUI_LABLE
#define GUI_LABLE

#include "GUI.h"
#include "TextRenderer.h"

#include <glm/glm.hpp>

#define SCALE_FACTOR 0.25

class GUILabel {
public:
    GUILabel(GUI* parent, const char* text, float size, glm::vec2 offset = glm::vec2(0.0f,0.0f), glm::vec4 color = glm::vec4(1.0f));
    GUILabel();
    ~GUILabel();

    GUI* getParent() {return _parent;}
    std::string getText() {return _text;}
    float getSize() {return _size;}
    glm::vec4 getColor() {return _color;}
    bool getVisible() {return _visible;}

    void setText(std::string text) {_text = text; printf("Text set\n");}
    void setVisible(bool visible) {_visible = visible;}

    void render(TextRenderer& renderer, TextShader* shader, int width, int height);

private:
    glm::vec2 _offset;
    GUI* _parent;
    std::string _text;
    glm::vec4 _color;
    float _size;

    bool _visible;

    glm::vec2 toPixelCoords(glm::vec2 coords, int width, int height);
};

#endif