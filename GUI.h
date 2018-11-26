#ifndef GUI_H
#define GUI_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <functional>

#include "GameObject.h"
#include "Texture.h"

enum GUIType
{
    GUI_BUTTON
};

class GUI : public GameObject
{
public:
    typedef std::function<void()> call;

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

    //Callbacks
    std::function<void()> callback() const {return eventCallback;}
    template<typename T, typename F, typename... Args>
    void subscribeEvent(T instance, F func, Args... args)
    {
        call temp = { std::bind(func, instance, args...) };
        eventCallback = temp;
    }

protected:
    GLuint _vaoID, _vboID;
    
    glm::vec2 _position;
    glm::vec2 _scale;
    glm::vec4 _uv;
    Texture _texture;

    GUIType _type;
    bool _mouseOver;
    bool _visible;

    call eventCallback;

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