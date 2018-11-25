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
}

void Renderer::init(StaticShader* shader, OutlineShader* outline, GUIShader* gui)
{
    _staticShader = shader;
    _outlineShader = outline;
    _guiShader = gui;
}

void Renderer::beginObjectRender()
{
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glClear(GL_STENCIL_BUFFER_BIT);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

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
        // glm::mat4 model = Math::createTransformationMatrix(obj->getPosition(), obj->getRotation(), obj->getScale());
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
        glm::mat4 transform = Math::createTransformationMatrix(gui->getPosition(), glm::vec2(0.0f), gui->getScale());
        _guiShader->loadTransformationMatrix(transform);
        _guiShader->loadTexture();
        
        gui->render();
    }

    _guiShader->stop();

    glEnable(GL_DEPTH_TEST);
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
    printf("object added ID=%d\n.  NEw list:\n",(int)id);
    for(unsigned int i = 0; i < _objects.size(); i++) {
        printf("objects[%d]: ID=%d\n", i, _objects[i]->getID());
    }
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

unsigned int Renderer::addGUI(float x, float y, float sx, float sy, std::string filePath)
{
    GUI* gui = new GUI(x,y,sx,sy,filePath);
    gui->setID(currentID++);
    _guis.push_back(gui);
    return gui->getID();
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