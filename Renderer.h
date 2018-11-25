#ifndef RENDERER
#define RENDERER

#include "Primitive.h"
#include "StaticShader.h"
#include "OutlineShader.h"
#include "Camera.h"
#include "Light.h"
#include "GUI.h"
#include "GUIShader.h"

#include <SDL2/SDL.h>
#include <vector>

class Renderer {
public:
    Renderer();
    ~Renderer();
    void init(StaticShader* shader, OutlineShader* outline, GUIShader* gui);
    void beginObjectRender();
    void renderObjects(Camera& camera);
    void endObjectRender();
    void renderGUIs();
    void endRender(SDL_Window* window);
    std::vector<unsigned int> getSelectedIDs();

    void unselectAllObjects();
    bool deleteObject(unsigned int id);

    unsigned int addCube(float x, float y, float z, float rx, float ry, float rz, 
                         float sx, float sy, float sz, Material& material);

    unsigned int addCube(float x, float y, float z, float rx, float ry, float rz, 
                         float sx, float sy, float sz);

    unsigned int addPointLight(float x, float y, float z, float r, float g, float b,
                          float intensity, float constant, float linear, float quadratic);

    unsigned int addDirectionalLight(float dx, float dy, float dz, float r, float g, float b, float instensity);

    unsigned int addGUI(float x, float y, float sx, float sy, glm::vec4 color);

    unsigned int getNumPrimitivesSelected();

    GameObject* getGameObject(unsigned int id);
    std::vector<Primitive*> getPrimitives() {return _objects;}

private:
    std::vector<Primitive*> _objects;
    std::vector<Light*> _lights;
    std::vector<GUI*> _guis;

    StaticShader* _staticShader;
    OutlineShader* _outlineShader;
    GUIShader* _guiShader;

    unsigned int currentID = 0;
};

#endif