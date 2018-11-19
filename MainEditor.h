#ifndef MAIN_EDITOR_H
#define MAIN_EDITOR_H

#define GL_GLEXT_PROTOTYPES

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <vector>

#include "StaticShader.h"
#include "OutlineShader.h"
#include "Camera.h"
#include "Renderer.h"
#include "Cube.h"
#include "InputManager.h"
#include "Timing.h"
#include "Material.h"
#include "Picker.h"
#include "TransformController.h"
#include "TransformShader.h"

class MainEditor
{
public:
    MainEditor() {}

    void run();

private:

    SDL_Window* window;
    StaticShader staticShader;
    OutlineShader outlineShader;
    Camera camera;
    Renderer renderer;
    InputManager inputManager;
    Timing timer;
    Picker picker;
    TransformController* transformController;
    TransformShader transformShader;

    unsigned int cube1, cube2, light, light1, light2, light3;

    float cameraSpeed = 0.015f;
    float intensity = 0.1f;

    int screenWidth = 1600;
    int screenHeight = 900;
    bool isRunning = false;

    glm::vec2 prevMouseCoords;

    void init();
    void updateSelections(std::vector<int>& selectedIds);
    bool updateTransformSelection();
    void update();
    void render();
    void gameLoop();
    void cleanUp();
};

#endif // MAIN_EDITOR