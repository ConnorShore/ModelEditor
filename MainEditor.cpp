#include "MainEditor.h"
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include "DirectionalLight.h"

#include "Math.h"

void MainEditor::init()
{
    isRunning = true;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    window = SDL_CreateWindow("Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth,screenHeight, SDL_WINDOW_OPENGL);

	if (window == nullptr) {
		printf("Failed to create SDL Window");
	}

	SDL_GLContext glContext;
	glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr) {
		printf("Failed to create GL Context");
	}

	glewExperimental = GL_TRUE;

	GLenum error;
	error = glewInit();
	if (error != GLEW_OK) {
		printf("Failed to initialize glew");
	}

	glClearColor(0.05f, 0.0f, 0.25f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    staticShader.init("Shaders/shader.vert", "Shaders/shader.frag");
    staticShader.bindAttributes();

    outlineShader.init("Shaders/outlineShader.vert", "Shaders/outlineShader.frag");
    outlineShader.bindAttributes();

    transformShader.init("Shaders/transformShader.vert", "Shaders/transformShader.frag");
    transformShader.bindAttributes();
    
    renderer.init(&staticShader, &outlineShader);

    camera.init(screenWidth, screenHeight);
    camera.setPosition(0.0f, 0.0f, 3.0f);

    transformController = new TransformController;

    Material mat;
    mat.ambient = glm::vec3(1.0f, 0.5f, 0.31f);
    mat.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
    mat.specular = glm::vec3(0.5f);
    mat.shininess = 32.0f;
    cube1 = renderer.addCube(0,0,0,  0,0,0,  1,1,1,  mat);

    Material mat2;
    mat2.ambient = glm::vec3(0.2f, 0.95f, 0.45f);
    mat2.diffuse = glm::vec3(0.2f, 0.95f, 0.45f);
    mat2.specular = glm::vec3(1.0f);
    mat2.shininess = 13.0f;
    renderer.addCube(2, -0.74, -3,      0,25,56, 1.25,1.75,1.25, mat2);
    
    light = renderer.addPointLight(1.2f,1.0f,2.0f,  0.15f,0.5f,1.0f,  1.0f,  1.0f,0.09f,0.032f);
    light1 = renderer.addPointLight(-1.2f,-0.5,-0.8f,  0.0f,0.0f,1.0f,  0.6f,  1.0f,0.09f,0.032f);
    light2 = renderer.addPointLight(0.0,1.5f,-1.0f,  0.0f,1.0f,0.0f,  0.4f,  1.0f,0.09f,0.032f);
    light3 = renderer.addDirectionalLight(1.0f,0.0f,-0.3f,   1.0f,1.0f,1.0f,   intensity);

    picker = Picker(&camera);
}

bool MainEditor::updateTransformSelection()
{
    bool selected = false;
    if(transformController->getXController()->isInSelectRange) {
        transformController->getXController()->isSelected = true;
        selected = true;
    } else {
        transformController->getXController()->isSelected = false;
    }

    if(transformController->getYController()->isInSelectRange) {
        transformController->getYController()->isSelected = true;
        selected = true;
    } else {
        transformController->getYController()->isSelected = false;
    }

    if(transformController->getZController()->isInSelectRange) {
        transformController->getZController()->isSelected = true;
        selected = true;
    } else {
        transformController->getZController()->isSelected = false;
    }

    transformController->setControlling(selected);
    return selected;
}

void MainEditor::updateSelections(std::vector<int>& selectedIds)
{
    selectedIds.clear();

    if(inputManager.isKeyDown(SDL_BUTTON_LEFT)) {

        if(updateTransformSelection())
            return;

        int ct = 0;
        std::vector<glm::vec3> positions;
        for(Primitive* obj : renderer.getPrimitives()) {
            if(obj->isInSelectRange) {
                obj->isSelected = true;
                positions.push_back(obj->getPosition());
                selectedIds.push_back(ct);
            } 
            else if((inputManager.isKeyDown(SDLK_LSHIFT) || inputManager.isKeyDown(SDLK_RSHIFT)) && obj->isSelected){
                positions.push_back(obj->getPosition());
                selectedIds.push_back(ct);
            }
            else {
                obj->isSelected = false;
            }
            ct++;
        }
        
        unsigned int size = positions.size();
        if(size == 0)
            transformController->setVisible(false);
        else {
            glm::vec3 sumPosition(0.0f);
            for(unsigned int i = 0; i < size; i++) {
                // printf("Position %d x: %f\n", i, positions[i].x);
                sumPosition += positions[i];
            }

            sumPosition /= size;
            transformController->setPosition(sumPosition);
            transformController->setVisible(true);
            // printf("Pos: %f,%f,%f\n", transformController->getPosition().x, transformController->getPosition().y, transformController->getPosition().z);
        }
    }
}

void MainEditor::update()
{

    inputManager.update();
    camera.setMouseCords(inputManager.getMouseX(), inputManager.getMouseY());
    camera.update();
    picker.update(renderer.getPrimitives(), transformController);

    // KEYBOARD //
    if(inputManager.isKeyDown(SDLK_w)) {
        camera.moveForward(cameraSpeed);
    }
    if(inputManager.isKeyDown(SDLK_s)) {
        camera.moveBackward(cameraSpeed);
    }
    if(inputManager.isKeyDown(SDLK_a)) {
        camera.moveLeft(cameraSpeed);
    }
    if(inputManager.isKeyDown(SDLK_d)) {
        camera.moveRight(cameraSpeed);
    }
    if(inputManager.isKeyDown(SDLK_e)) {
        camera.moveUp(cameraSpeed);
    }
    if(inputManager.isKeyDown(SDLK_q)) {
        camera.moveDown(cameraSpeed);
    }
    if(inputManager.isKeyDown(SDLK_UP)) {
        camera.rotateUp(0.5f);
    }
    if(inputManager.isKeyDown(SDLK_DOWN)) {
        camera.rotateDown(0.5f);
    }
    if(inputManager.isKeyDown(SDLK_LEFT)) {
        camera.rotateLeft(0.5f);
    }
    if(inputManager.isKeyDown(SDLK_RIGHT)) {
        camera.rotateRight(0.5f);
    }

    if(inputManager.isKeyDown(SDLK_1)) {
        DirectionalLight* d = static_cast<DirectionalLight*>(renderer.getGameObject(light3));
        intensity += 0.05;
        d->setIntensity(intensity);
    }
    if(inputManager.isKeyDown(SDLK_2)) {
        DirectionalLight* d = static_cast<DirectionalLight*>(renderer.getGameObject(light3));
        intensity -= 0.05;
        d->setIntensity(intensity);
    }

    //Releases
    if(!inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
        transformController->deselectAxis();
    }

    std::vector<int> ids;
    // printf("IDs size before: %d\n", ids.size());
    updateSelections(ids);
    // printf("IDs size after: %d\n", ids.size());

    //Move object and transform if needed
    if(transformController->inControl()) {
        glm::vec2 mouseCoords = glm::vec2(inputManager.getMouseX(), inputManager.getMouseY());
        if(transformController->getXController()->isSelected) {
            // float distance = mouseCoords.x - prevMouseCoords.x;
            //May need to convert from screen to world coords here and get the x component
            glm::vec3 coords = picker.screenToWorldCoords(mouseCoords.x, mouseCoords.y);
            glm::vec3 prev = picker.screenToWorldCoords(prevMouseCoords.x, prevMouseCoords.y);
            float distance = coords.x - prev.x;
            transformController->moveX(distance);
            printf("Controller new x: %f\n", transformController->getPosition().x);

            for(Primitive* obj : renderer.getPrimitives()) {
                if(obj->isSelected) {
                    obj->setPosition(glm::vec3(obj->getPosition().x + distance, obj->getPosition().y, obj->getPosition().z));
                    printf("object new x: %f\n", obj->getPosition().x);
                }
            }
        }
        // else if(transformController->getYController()->isSelected) {
        //     moveDir = glm::vec3(0.0f, 1.0f, 0.0f);
        // }
        // else if(transformController->getZController()->isSelected) {
        //     moveDir = glm::vec3(0.0f, 0.0f, 1.0f);
        // } else {
        //     printf("In control however no axis selected\n");
        // }

        prevMouseCoords = mouseCoords;
    }
}

void MainEditor::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDepthRange(0.01, 1);
    renderer.beginObjectRender();
    renderer.renderObjects(camera);
    renderer.endObjectRender();

    glDepthRange(0.0, 0.01);
    transformController->render(camera, transformShader);

    glDepthRange(0,1);
    renderer.endRender(window);
}

void MainEditor::gameLoop()
{
    timer.TimeInit();
    while(isRunning) {
        timer.FpsLimitInit();
        timer.calcDeltaTime();

        update();
        render();

        timer.CalculateFPS(true);
    }
}

void MainEditor::cleanUp()
{
    SDL_DestroyWindow(window);
}

void MainEditor::run()
{
    init();
    gameLoop();
    cleanUp();
}