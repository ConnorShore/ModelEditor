#include "Renderer.h"
#include "Math.h"
#include "Cube.h"

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

void Renderer::init(StaticShader* shader)
{
    _staticShader = shader;
}

void Renderer::beginRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_staticShader->start();
	_staticShader->getUniformLocations();
}

void Renderer::renderObjects(Camera& camera)
{
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = camera.getProjectionMatrix();

    _staticShader->loadViewMatrix(view);
    _staticShader->loadProjectionMatrix(proj);

    for(Light* light : _lights) {
        //Will only render props for the last light in _lights
        _staticShader->loadLightPosition(light->getPosition());
        _staticShader->loadLightColor(light->getColor());
    }

    for(Primitive* obj : _objects) {
        glm::mat4 model = Math::createTransformationMatrix(obj->getPosition(), obj->getRotation(), obj->getScale());

        _staticShader->loadModelMatrix(model);
        
        obj->render();
    }
}

void Renderer::endRender(SDL_Window* window)
{
    _staticShader->stop();

    SDL_GL_SwapWindow(window);
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
                               float sx, float sy, float sz, float r, float g, float b, float a)
{
    Cube* cube = new Cube(x,y,z,rx,ry,rz,sx,sy,sz,r,g,b,a);
    cube->setID(currentID++);
    _objects.push_back(cube);

    return cube->getID();
}

unsigned int Renderer::addLight(float x, float y, float z, float r, float g, float b)
{
    Light* light = new Light(x,y,z,r,g,b);
    light->setID(currentID++);
    _lights.push_back(light);
    return light->getID();
}