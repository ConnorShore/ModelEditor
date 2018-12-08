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
#include "GUIShader.h"
#include "TextShader.h"
#include "TextRenderer.h"
#include "GUILabel.h"

enum TransformMode
{
    POSITION,
    SCALE
};

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
    GUIShader guiShader;
    TextRenderer textRenderer;
    TextShader textShader;

    TransformMode _tMode = POSITION;

    GUILabel* description;

    unsigned int cube1, cube2, light, light1, light2, light3, panel, addCube, deleteCube;

    float cameraSpeed = 0.015f;
    float intensity = 0.1f;

    int screenWidth = 1600;
    int screenHeight = 900;
    bool isRunning = false;
    bool guiControl = false;

    glm::vec3 transformSelectLoc;

    glm::vec3 scaleTransformLoc;
    bool scaleTransformSet;

    void init();
    void updateScaleAdjustments(glm::vec3& origin, glm::vec3& direction);
    void updatePositionAdjustments(glm::vec3& origin, glm::vec3& direction);
    void updateSelections(std::vector<int>& selectedIds);
    bool updateTransformSelection();
    void input();
    void updateGUIs();
    void update();
    void render();
    void gameLoop();
    void cleanUp();

    //Callbacks
    void createCube();
    void deleteCubes();
    void setTransfromMode(TransformMode mode);
};

#endif // MAIN_EDITOR