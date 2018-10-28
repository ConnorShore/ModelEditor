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

unsigned int Renderer::addCube(float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz)
{
    Cube* cube = new Cube(x,y,z,rx,ry,rz,sx,sy,sz);
    cube->setID(current_id++);
    _objects.push_back(cube);

    return cube->getID();
}