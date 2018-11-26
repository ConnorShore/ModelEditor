#ifndef GUI_H
#define GUI_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "GameObject.h"
#include "Texture.h"

enum GUIType
{
    BUTTON
};

class GUI : public GameObject
{
public:
    GUI(float x, float y, float sx, float sy, std::string& textureFile);
    GUI();
    ~GUI();

    virtual void update() = 0;

    bool inBounds(glm::vec2 coords);
    void render();

    // return: [minX, maxX, minY, maxY]
    glm::vec4 getBounds();

    glm::vec2 getPosition() {return _position;}
    glm::vec2 getScale() {return _scale;}
    Texture getTexture() {return _texture;}

    GUIType getType() {return _type;}
    bool getMouseOver() {return _mouseOver;}
    bool isVisible() {return _visible;}

    void setMouseOver(bool mouseOver) {_mouseOver = mouseOver;}
    void setVisible(bool visible) {_visible = visible;}

protected:
    GLuint _vaoID, _vboID;
    
    glm::vec2 _position;
    glm::vec2 _scale;
    glm::vec4 _uv;
    Texture _texture;

    GUIType _type;
    bool _mouseOver;
    bool _visible;

    void createIDs();

    float _vertices[10] = {
        1,1,
        1,-1,
        -1,-1,
        -1,1,
        1,1
    };
};

#endif