#include "Renderer.h"
#include "Math.h"
#include "Cube.h"
#include "PointLight.h"
#include "DirectionalLight.h"

#include <algorithm>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
    for(unsigned int i = _objects.size()-1; i >= 0; i--) {
        delete _objects.back();
        _objects.pop_back();
    }
    for(unsigned int i = _lights.size()-1; i >= 0; i--) {
        delete _lights.back();
        _lights.pop_back();
    }
    for(unsigned int i = _guis.size()-1; i >= 0; i--) {
        delete _guis.back();
        _guis.pop_back();
    }
    for(unsigned int i = _labels.size()-1; i >= 0; i--) {
        delete _labels.back();
        _labels.pop_back();
    }
}

void Renderer::init(StaticShader* shader, OutlineShader* outline, GUIShader* gui, TextShader* text, int width, int height)
{
    _staticShader = shader;
    _outlineShader = outline;
    _guiShader = gui;
    _textShader = text;

    _width = width;
    _height = height;

    _textRenderer.init(_textShader, _width, _height);
}

void Renderer::beginObjectRender()
{
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glClear(GL_STENCIL_BUFFER_BIT);

	_staticShader->start();
	_staticShader->getUniformLocations();
}

void Renderer::renderObjects(Camera& camera)
{
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = camera.getProjectionMatrix();

    _staticShader->loadViewMatrix(view);
    _staticShader->loadProjectionMatrix(proj);
    _staticShader->loadViewPosition(camera.getPosition());

    _staticShader->loadLights(_lights);

    glStencilFunc(GL_ALWAYS, 0x1, 0x1);
    glStencilMask(0x1);

    for(Primitive* obj : _objects) {
        glm::mat4 model = obj->getModelMatrix();
        _staticShader->loadModelMatrix(model);
        _staticShader->loadMaterial(obj->getMaterial());
        
        obj->render();
    }

    _staticShader->stop();

    _outlineShader->start();
    _outlineShader->getUniformLocations();
    _outlineShader->loadProjectionMatrix(proj);
    _outlineShader->loadViewMatrix(view);

    glStencilFunc(GL_NOTEQUAL, 0x1, 0x1);
    glStencilMask(0x0);
    glDisable(GL_DEPTH_TEST);

     for(Primitive* obj : _objects) {
        float factor = 1.05f;
        glm::vec3 scale = obj->getScale() * factor;
        glm::mat4 model = Math::createTransformationMatrix(obj->getPosition(), obj->getRotation(), scale);

        _outlineShader->loadModelMatrix(model);
        _outlineShader->loadIsSelected(obj->isSelected);
        
        obj->render();
    }

    _outlineShader->stop();

    glEnable(GL_DEPTH_TEST);
    glStencilMask(0x1);
}

void Renderer::endObjectRender()
{
    //maybe move up right under glStencilMask or right after glEnable(DEPTHTEST)
    glDisable(GL_STENCIL_TEST);
}

void Renderer::renderGUIs()
{
    glDisable(GL_DEPTH_TEST);
    
    _guiShader->start();
    _guiShader->getUniformLocations();
    
    for(GUI* gui : _guis)
    {
        if(!gui->isVisible())
            continue;

        glm::mat4 transform = Math::createTransformationMatrix(gui->getPosition(), glm::vec2(0.0f), gui->getScale());
        _guiShader->loadTransformationMatrix(transform);
        _guiShader->loadTexture();
        _guiShader->loadAlpha(gui->getAlpha());
        
        gui->render();
    }

    _guiShader->stop();

    renderGUILabels();

    glEnable(GL_DEPTH_TEST);
}

void Renderer::renderGUILabels()
{
    _textRenderer.prepare(_textShader);

    for(GUILabel* label : _labels) {
        if(label->getParent()->isVisible()) {
            label->render(_textRenderer, _textShader, _width, _height);
        }
    }

    _textRenderer.end(_textShader);
}

void Renderer::endRender(SDL_Window* window)
{
    SDL_GL_SwapWindow(window);
}

void Renderer::unselectAllObjects()
{
    for(Primitive* obj : _objects) {
        obj->isSelected = false;
    }
}

bool Renderer::deleteObject(unsigned int id)
{
    unselectAllObjects();
    
    int deleteIndex = -1;
    for(unsigned int i = 0; i < _objects.size(); i++) {
        if(_objects[i]->getID() == id) {
            deleteIndex = i;
            break;
        }
    }

    if(deleteIndex != -1) {
        if(_objects.size() > 1)
            std::swap(_objects[deleteIndex], _objects.back());
        delete _objects.back();
        _objects.pop_back();
        return true;
    }

    return false;
}

std::vector<unsigned int> Renderer::getSelectedIDs()
{
    std::vector<unsigned int> ids;
    for(unsigned int i = 0; i < _objects.size(); i++) {
        if(_objects[i]->isSelected)
            ids.push_back(_objects[i]->getID());
    }

    return ids;
}

GameObject* Renderer::getGameObject(unsigned int id)
{
    GameObject* temp = nullptr;
    for(unsigned int i = 0; i < _objects.size(); i++) {
        if(_objects[i]->getID() == id) {
            temp = _objects[i];
            return temp;
        }
    }

    for(unsigned int i = 0; i < _lights.size(); i++) {
        if(_lights[i]->getID() == id) {
            temp = _lights[i];
            return temp;
        }
    }

    for(unsigned int i = 0; i < _guis.size(); i++) {
        if(_guis[i]->getID() == id) {
            temp = _guis[i];
            return temp;
        }
    }

    return temp;
}

unsigned int Renderer::addCube(float x, float y, float z, float rx, float ry, float rz, 
                               float sx, float sy, float sz, Material& material)
{
    Cube* cube = new Cube(x,y,z,rx,ry,rz,sx,sy,sz,material);
    cube->setID(currentID++);
    _objects.push_back(cube);

    return cube->getID();
}

unsigned int Renderer::addCube(float x, float y, float z, float rx, float ry, float rz, 
                               float sx, float sy, float sz)
{
    Material matDefault;
    matDefault.ambient = glm::vec3(0.5, 0.5, 0.5);
    matDefault.diffuse = glm::vec3(0.5, 0.5, 0.5);
    matDefault.specular = glm::vec3(0.5, 0.5, 0.5);
    matDefault.shininess = 5.0f;

    unsigned int id = addCube(x,y,z,rx,ry,rz,sx,sy,sz,matDefault);

    return id;
}

unsigned int Renderer::addPointLight(float x, float y, float z, float r, float g, float b, float intensity,
                                float constant, float linear, float quadratic)
{
    glm::vec3 pos(x,y,z);
    glm::vec3 color(r,g,b);
    glm::vec3 attenuation(constant,linear,quadratic);
    PointLight* light = new PointLight(pos,color,intensity,attenuation);

    light->setID(currentID++);
    _lights.push_back(light);
    return light->getID();
}


unsigned int Renderer::addDirectionalLight(float dx, float dy, float dz, float r, float g, float b, float intensity)
{
    glm::vec3 direction(dx,dy,dz);
    glm::vec3 color(r,g,b);
    DirectionalLight* light = new DirectionalLight(direction,color,intensity);

    light->setID(currentID++);
    _lights.push_back(light);
    return light->getID();
}

Button* Renderer::addButton(GUI* parent, float x, float y, float sx, float sy, std::string filePath, std::string description, bool relativePos, unsigned int* id)
{
    Button* button = new Button(parent,x,y,sx,sy,filePath,description,relativePos);
    button->setID(currentID++);
    _guis.push_back(button);
    if(id != nullptr)
        *id = button->getID();
    return button;
}

Button* Renderer::addButton(float x, float y, float sx, float sy, std::string filePath, unsigned int* id)
{
    Button* button = new Button(x,y,sx,sy,filePath);
    button->setID(currentID++);
    _guis.push_back(button);
    if(id != nullptr)
        *id = button->getID();
    return button;
}

Panel* Renderer::addPanel(GUI* parent, float x, float y, float sx, float sy, std::string filePath, bool relativePos, unsigned int* id)
{
    Panel* panel = new Panel(parent,x,y,sx,sy,filePath,relativePos);
    panel->setID(currentID++);
    _guis.push_back(panel);
    if(id != nullptr)
        *id = panel->getID();
    return panel;
}
Panel* Renderer::addPanel(float x, float y, float sx, float sy, std::string filePath, unsigned int* id)
{
    Panel* panel = new Panel(x,y,sx,sy,filePath);
    panel->setID(currentID++);
    _guis.push_back(panel);
    if(id != nullptr)
        *id = panel->getID();
    return panel;
}

GUILabel* Renderer::attachLabel(GUI* parent, const char* text, float size, glm::vec2 offset, glm::vec4 color)
{
    // TODO: ADD OFFSET IN HERE AND FIGURE OUT ISSUES
    GUILabel* label = new GUILabel(parent, text, size, color);
    _labels.push_back(label);
    return label;
}

unsigned int Renderer::getNumPrimitivesSelected()
{
    unsigned int ct = 0;
    for(Primitive* obj : _objects) {
        if(obj->isSelected)
            ct++;
    }
    return ct;
}

void Renderer::setWidthAndHeight(int width, int height)
{
    _width = width;
    _height = height;
}