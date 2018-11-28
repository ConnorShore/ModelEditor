#include "GUI.h"
#include "Loader.h"

GUI::GUI(GUI* parent, float x, float y, float sx, float sy, std::string& textureFile, bool relativePos /* true */)
{
    printf("IN GUI Constructorn 1\n");
    _vaoID = 0;
    _vboID = 0;
    
    if(relativePos)
        _position = parent->getPosition() + glm::vec2(x,y);
    else
        _position = glm::vec2(x,y);

    _scale = glm::vec2(sx, sy);
    _texture = Loader::loadPNG(textureFile);
    _uv = glm::vec4(0,0,1,1);
    _visible = true;
    _parent = parent;
    _parent->addChild(this);

    createIDs();
}

GUI::GUI(float x, float y, float sx, float sy, std::string& textureFile)
{
    printf("IN GUI Constructorn 2\n");
    _vaoID = 0;
    _vboID = 0;
    _position = glm::vec2(x,y);
    _scale = glm::vec2(sx, sy);
    _texture = Loader::loadPNG(textureFile);
    _uv = glm::vec4(0,0,1,1);
    _visible = true;
    printf("About to assign parent nullptr\n");
    _parent = nullptr;

    createIDs();
}

GUI::GUI()
{
    printf("IN GUI Constructorn 3\n");
    _vaoID = 0;
    _vboID = 0;
    _position = glm::vec2(0.0f);
    _scale = glm::vec2(1.0f);
    _uv = glm::vec4(0,0,1,1);
    _visible = true;
    _parent = nullptr;

    createIDs();
}

GUI::~GUI()
{
}

void GUI::createIDs()
{
    glGenVertexArrays(1, &_vaoID);
    glGenBuffers(1, &_vboID);

    glBindVertexArray(_vaoID);

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glBufferData(GL_ARRAY_BUFFER, 10 * sizeof(float), &_vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

bool GUI::inBounds(glm::vec2 coords)
{
    glm::vec4 bounds = getBounds();
    return coords.x > bounds.x && coords.x < bounds.y && coords.y > bounds.z && coords.y < bounds.w;
}

void GUI::render()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture.id);
    
    glBindVertexArray(_vaoID);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 10);
    glBindVertexArray(0);
}

glm::vec4 GUI::getBounds()
{
    glm::vec4 bounds;
    bounds.x = _position.x - _scale.x;
    bounds.y = _position.x + _scale.x;
    bounds.z = _position.y - _scale.y;
    bounds.w = _position.y + _scale.y;
    return bounds;
}

void GUI::addChild(GUI* child)
{
    bool exists = false;
    for(unsigned int i = 0; i < _children.size(); i++)
        if(_children[i]->getID() == child->getID())
            exists = true;
    if(!exists)
        _children.push_back(child);
    else
        printf("Child [%d] already exists\n", child->getID());
}