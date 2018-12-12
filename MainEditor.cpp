#include "MainEditor.h"
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <sstream>

#include "DirectionalLight.h"
#include "Math.h"
#include "Button.h"
#include "Sphere.h"

template<typename T>
std::string truncate(const T val, const int truncVal = 2)
{
    std::ostringstream out;
    out.precision(truncVal);
    out << std::fixed << val;
    return out.str();
}

void MainEditor::init()
{
    isRunning = true;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    window = SDL_CreateWindow("Connor Shore - Final Project: Deep Learning Model Editor", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth,screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

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
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    staticShader.init("Shaders/shader.vert", "Shaders/shader.frag");
    staticShader.bindAttributes();

    outlineShader.init("Shaders/outlineShader.vert", "Shaders/outlineShader.frag");
    outlineShader.bindAttributes();

    transformShader.init("Shaders/transformShader.vert", "Shaders/transformShader.frag");
    transformShader.bindAttributes();

    guiShader.init("Shaders/guiShader.vert", "Shaders/guiShader.frag");
    guiShader.bindAttributes();

    textShader.init("Shaders/textShader.vert", "Shaders/textShader.frag");
    textShader.bindAttributes();
    
    renderer.init(&staticShader, &outlineShader, &guiShader, &textShader, screenWidth, screenHeight);

    camera.init(screenWidth, screenHeight);
    camera.setPosition(0.0f, 0.0f, 3.0f);

    picker = Picker(&camera);

    transformController = new TransformController;

    Material mat;
    mat.ambient = glm::vec3(1.0f, 0.5f, 0.31f);
    mat.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
    mat.specular = glm::vec3(0.5f);
    mat.shininess = 32.0f;
    // cube1 = renderer.addCube(0,0,0,  0,0,0,  1,1,1,  mat);
    renderer.addSphere(0,0,0, 1, mat);

    // Material mat2;
    // mat2.ambient = glm::vec3(0.2f, 0.95f, 0.45f);
    // mat2.diffuse = glm::vec3(0.2f, 0.95f, 0.45f);
    // mat2.specular = glm::vec3(1.0f);
    // mat2.shininess = 13.0f;
    // renderer.addCube(2,-0.75,-3,  0,25,56,  1.25,1.75,1.25,  mat2);
    
    light = renderer.addPointLight(1.2f,1.0f,2.0f,  0.15f,0.5f,1.0f,  1.0f,  1.0f,0.09f,0.032f);
    light1 = renderer.addPointLight(-1.2f,-0.5,-0.8f,  0.0f,0.0f,1.0f,  0.6f,  1.0f,0.09f,0.032f);
    light2 = renderer.addPointLight(0.0,1.5f,-1.0f,  0.0f,1.0f,0.0f,  0.4f,  1.0f,0.09f,0.032f);
    light3 = renderer.addDirectionalLight(1.0f,0.0f,-0.3f,   1.0f,1.0f,1.0f,   intensity);

    float aspect = (float)screenWidth/(float)screenHeight;

    Panel* topBar = renderer.addPanel(0.0f, 0.92f, 1.0f, 0.08f, "Textures/panel.png", &top);

    Button* addCubeButton = renderer.addButton(topBar, -0.95f, 0.0, 0.035f, 0.035f * aspect, "Textures/addCube.png", "Add Cube", true, &addCube);
    addCubeButton->subscribeEvent(this, &MainEditor::createCube);

    Button* deleteCubeButton = renderer.addButton(topBar, -0.85f, 0.0, 0.035f, 0.035f * aspect, "Textures/deleteCube.png", "Delete Cube", true, &addCube);
    deleteCubeButton->subscribeEvent(this, &MainEditor::deleteCubes);

    Button* positionButton = renderer.addButton(topBar, -0.73f, 0.0f, 0.06f ,0.035f * aspect, "Textures/addCube.png", "Position", true, &position);
    positionButton->subscribeEvent(this, &MainEditor::setTransfromMode, POSITION);

    Button* sizeButton = renderer.addButton(topBar, -0.585f, 0.0f, 0.06f ,0.035f * aspect, "Textures/deleteCube.png", "Scale", true, &size);
    sizeButton->subscribeEvent(this, &MainEditor::setTransfromMode, SCALE);

    Panel* sidePanel = renderer.addPanel(0.7f, 0.0f, 0.3f, 1.0f, "Textures/panel.png", &panel);
    sidePanel->setAlpha(0.8f);

    Panel* statusPanel = renderer.addPanel(0.7, -0.925, 0.3, 0.125, "Textures/panel.png");
    transformMode = renderer.attachLabel(statusPanel, "Mode: Position", 1.25f, glm::vec2(0.0f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
    description = renderer.attachLabel(statusPanel, std::string().c_str(), 1.25f, glm::vec2(0.0f, -0.05f), glm::vec4(1.0f));

    //Transform properties
    positionValues = renderer.attachLabel(statusPanel, std::string().c_str(), 1.2f, glm::vec2(0.0f, 0.8f), glm::vec4(1.0f));
    rotationValues = renderer.attachLabel(statusPanel, std::string().c_str(), 1.2f, glm::vec2(0.0f, 0.7f), glm::vec4(1.0f));
    scaleValues = renderer.attachLabel(statusPanel, std::string().c_str(), 1.2f, glm::vec2(0.0f, 0.6f), glm::vec4(1.0f));
}

bool MainEditor::updateTransformSelection()
{
    //Dont need to set axis selection if already in control of transform controller
    if(transformController->inControl())
        return true;

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

    if(!selected) {
        transformController->selectLocUpdated = false;
    }

    //Check if all axis are in select range
    if(transformController->getXController()->isSelected &&
            transformController->getYController()->isSelected &&
            transformController->getZController()->isSelected) {
        transformController->setAllAxisSelected(true);
    } else {
        transformController->setAllAxisSelected(false);
    }

    transformController->setControlling(selected);

    if(selected && !scaleTransformSet){
        glm::vec3 origin, direction;
        picker.calculateRay(&origin, &direction);

        glm::vec3 intersectLocation;
        Plane plane;
        plane.origin = transformController->getPosition();
        plane.normal = camera.getDirection();
        picker.rayPlaneIntersection(origin, direction, plane, &intersectLocation);
        scaleTransformLoc = intersectLocation;
        scaleTransformSet = true;
    }

    return selected;
}

void MainEditor::updateSelections(std::vector<int>& selectedIds)
{   
    selectedIds.clear();

    if(renderer.getNumPrimitivesSelected() > 0) {
        for(Primitive* obj : renderer.getPrimitives()) {
            if(obj->isSelected) {
                std::string posText = "Position: " + truncate(obj->getPosition().x) + " " + truncate(obj->getPosition().y) + " " + truncate(obj->getPosition().z);
                positionValues->setText(posText);            
                positionValues->setVisible(true);

                std::string rotText = "Rotation: " + truncate(obj->getRotation().x) + " " + truncate(obj->getRotation().y) + " " + truncate(obj->getRotation().z);
                rotationValues->setText(rotText);            
                rotationValues->setVisible(true);

                std::string scaleText = "   Scale: " + truncate(obj->getScale().x) + " " + truncate(obj->getScale().y) + " " + truncate(obj->getScale().z);
                scaleValues->setText(scaleText);            
                scaleValues->setVisible(true);
                break;
            }
        }
    } else {
        positionValues->setVisible(false);
        rotationValues->setVisible(false);
        scaleValues->setVisible(false);
    }

    if(inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> rotations;
        std::vector<glm::vec3> scales;

        if(updateTransformSelection() && renderer.getNumPrimitivesSelected() > 0)
            return;
        
        unsigned int ct = 0;
        for(Primitive* obj : renderer.getPrimitives()) {

            if(obj->isInSelectRange) {
                obj->selectedLocation = obj->getPosition();
                obj->isSelected = true;
                positions.push_back(obj->getPosition());
                rotations.push_back(obj->getRotation());
                scales.push_back(obj->getScale());
                selectedIds.push_back(ct);
            } 
            else if((inputManager.isKeyDown(SDLK_LSHIFT) || inputManager.isKeyDown(SDLK_RSHIFT)) && obj->isSelected){
                positions.push_back(obj->getPosition());
                rotations.push_back(obj->getRotation());
                scales.push_back(obj->getScale());
                selectedIds.push_back(ct);
                obj->selectedLocation = obj->getPosition();
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
            glm::vec3 sumRotation(0.0f);
            for(unsigned int i = 0; i < size; i++) {
                sumPosition += positions[i];
                sumRotation += rotations[i];
            }

            sumPosition /= size;
            sumRotation /= size;
            transformController->setPosition(sumPosition);
            
            //Keep controller to same rotation as objects
            // if(_tMode == SCALE)
            //     transformController->setRotation(sumRotation);
                
            transformController->setVisible(true);
            transformSelectLoc = transformController->getPosition();
            transformController->selectLocUpdated = true;
        }
    } else {
        scaleTransformSet = false;

         for(Primitive* obj : renderer.getPrimitives()) {
             if(obj->isSelected) {
                obj->setBaseScale(obj->getScale());
                glm::vec3 size = obj->getScale();
                glm::vec3 aabbMin = glm::vec3(-0.5f*size.x*size.x, -0.5f*size.y*size.y, -0.5f*size.z*size.z);
                glm::vec3 aabbMax = glm::vec3(0.5f*size.x*size.x, 0.5f*size.y*size.y, 0.5f*size.z*size.z);
                obj->setBoundingBox(aabbMin, aabbMax);
             }
         }
    }
}

void MainEditor::input()
{
    inputManager.update();

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
    if(transformController->inControl() && !inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
        transformController->deselectAxis();
        transformController->setControlling(false);
    }
}

void MainEditor::updateGUIs()
{
    if(scaleTransformSet) return;

    bool descriptionVisible = false;
    bool control = false;
    glm::vec2 mouse = camera.screenToNDC();
    
    std::vector<GUI*> guis = renderer.getGUIs();
    for(unsigned int i = 0; i < guis.size(); i++) {
        guis[i]->update();

        if(guis[i]->inBounds(mouse)) {
            GUIType type = guis[i]->getType();
            if(type == GUI_BUTTON) {
                Button* button = static_cast<Button*>(guis[i]);
                description->setText(button->getDescription());
                descriptionVisible = true;
            }
            
            control = true;
            if(inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
                switch(type) {
                    case GUI_BUTTON:
                        Button* button;
                        button = static_cast<Button*>(guis[i]);
                        button->onClick();
                        break;
                    case GUI_PANEL:
                    default:
                        break;
                }
            }
        }
    }

    description->setVisible(descriptionVisible);
    guiControl = control;
}

void MainEditor::updateScaleAdjustments(glm::vec3& origin, glm::vec3& direction)
{
    glm::vec3 intersectLocation;
    //All axis
    if(transformController->allAxisSelected()) {
        Plane plane;
        plane.origin = transformController->getPosition();
        plane.normal = camera.getDirection();
        picker.rayPlaneIntersection(origin, direction, plane, &intersectLocation);

        float size = (intersectLocation.x - scaleTransformLoc.x) + (intersectLocation.y - scaleTransformLoc.y) + (intersectLocation.z - scaleTransformLoc.z);

        for(Primitive* obj : renderer.getPrimitives()) {
            if(obj->isSelected) {
                glm::vec3 offset(0.0f);
                obj->setScale(obj->getBaseScale() + glm::vec3(size));
            }
        }
    } 
    
    //X Axis
    else if(transformController->getXController()->isSelected) {
        Plane plane;
        plane.origin = transformController->getPosition();
        plane.normal = glm::vec3(0,0,-1);
        picker.rayPlaneIntersection(origin, direction, plane, &intersectLocation);

        float size = (intersectLocation.x - scaleTransformLoc.x);

        for(Primitive* obj : renderer.getPrimitives()) {
            if(obj->isSelected) {
                glm::vec3 offset(0.0f);
                obj->setScale(obj->getBaseScale() + glm::vec3(size, 0.0f, 0.0f));
                if(dynamic_cast<Sphere*>(obj) != nullptr)
                    obj->setScale(obj->getBaseScale() + glm::vec3(size));
            }
        }
    }

    //Y Axis
    else if(transformController->getYController()->isSelected) {
        Plane plane;
        plane.origin = transformController->getPosition();
        plane.normal = glm::vec3(0,0,-1);
        picker.rayPlaneIntersection(origin, direction, plane, &intersectLocation);
        
        float size = (intersectLocation.y - scaleTransformLoc.y);

        for(Primitive* obj : renderer.getPrimitives()) {
            if(obj->isSelected) {
                glm::vec3 offset(0.0f);
                obj->setScale(obj->getBaseScale() + glm::vec3(0.0f, size, 0.0f));
                if(dynamic_cast<Sphere*>(obj) != nullptr)
                    obj->setScale(obj->getBaseScale() + glm::vec3(size));
            }
        }
    }

    //Z Axis
    else if(transformController->getZController()->isSelected) {
        Plane plane;
        plane.origin = transformController->getPosition();
        plane.normal = glm::vec3(0,1,0);
        picker.rayPlaneIntersection(origin, direction, plane, &intersectLocation);

        float size = (intersectLocation.z - scaleTransformLoc.z);

        for(Primitive* obj : renderer.getPrimitives()) {
            if(obj->isSelected) {
                glm::vec3 offset(0.0f);
                obj->setScale(obj->getBaseScale() + glm::vec3(0.0f, 0.0f, size));
                if(dynamic_cast<Sphere*>(obj) != nullptr)
                    obj->setScale(obj->getBaseScale() + glm::vec3(size));
            }
        }
    } 

    else {
        printf("In control however no axis selected\n");
    }
    
}

void MainEditor::updatePositionAdjustments(glm::vec3& origin, glm::vec3& direction)
{
    glm::vec3 intersectLocation;
    //All axis
    if(transformController->allAxisSelected()) {
        Plane plane;
        plane.origin = transformController->getPosition();
        plane.normal = camera.getDirection();
        if(picker.rayPlaneIntersection(origin, direction, plane, &intersectLocation)) {
            transformController->setPosition(glm::vec3(intersectLocation.x, intersectLocation.y, intersectLocation.z));
        }
        for(Primitive* obj : renderer.getPrimitives()) {
            if(obj->isSelected) {
                glm::vec3 offset(0.0f);
                offset = obj->selectedLocation - transformSelectLoc;
                obj->setPosition(transformController->getPosition() + offset);
                // obj->setPosition(glm::vec3(transformController->getPosition().x + offset.x, obj->getPosition().y, obj->getPosition().z));
            }
        }
    } 
    
    //X Axis
    else if(transformController->getXController()->isSelected) {
        Plane plane;
        plane.origin = transformController->getPosition();
        plane.normal = glm::vec3(0,0,-1);
        if(picker.rayPlaneIntersection(origin, direction, plane, &intersectLocation)) {
            transformController->setPosition(glm::vec3(intersectLocation.x, transformController->getPosition().y,
                                            transformController->getPosition().z));
        }

        for(Primitive* obj : renderer.getPrimitives()) {
            if(obj->isSelected) {
                glm::vec3 offset(0.0f);
                offset = obj->selectedLocation - transformSelectLoc;
                    obj->setPosition(glm::vec3(transformController->getPosition().x + offset.x, obj->getPosition().y, obj->getPosition().z));
            }
        }
    }

    //Y Axis
    else if(transformController->getYController()->isSelected) {
        Plane plane;
        plane.origin = transformController->getPosition();
        plane.normal = glm::vec3(0,0,-1);
        if(picker.rayPlaneIntersection(origin, direction, plane, &intersectLocation)) {
            transformController->setPosition(glm::vec3(transformController->getPosition().x, intersectLocation.y,
                                            transformController->getPosition().z));
        }
        
        for(Primitive* obj : renderer.getPrimitives()) {
            if(obj->isSelected) {
                glm::vec3 offset(0.0f);
                offset = obj->selectedLocation - transformSelectLoc;
                obj->setPosition(glm::vec3(obj->getPosition().x, transformController->getPosition().y + offset.y, obj->getPosition().z));
            }
        }
    }

    //Z Axis
    else if(transformController->getZController()->isSelected) {
        Plane plane;
        plane.origin = transformController->getPosition();
        plane.normal = glm::vec3(0,1,0);
        if(picker.rayPlaneIntersection(origin, direction, plane, &intersectLocation)) {
            transformController->setPosition(glm::vec3(transformController->getPosition().x, transformController->getPosition().y,
                                            intersectLocation.z));
        }

        for(Primitive* obj : renderer.getPrimitives()) {
            if(obj->isSelected) {
                glm::vec3 offset(0.0f);
                offset = obj->selectedLocation - transformSelectLoc;
                obj->setPosition(glm::vec3(obj->getPosition().x, obj->getPosition().y, transformController->getPosition().z + offset.z));
            }
        }
    } 

    else {
        printf("In control however no axis selected\n");
    }
}

void MainEditor::update()
{
    SDL_GetWindowSize(window, &screenWidth, &screenHeight);
    glViewport(0,  0, screenWidth, screenHeight);
    camera.setScreenDimensions(screenWidth, screenHeight);
    textRenderer.setWidthAndHeight(screenWidth, screenHeight);
    renderer.setWidthAndHeight(screenWidth, screenHeight);

    camera.setMouseCords(inputManager.getMouseX(), inputManager.getMouseY());
    camera.update();
    picker.update(renderer.getPrimitives(), transformController);

    updateGUIs();

    if(guiControl)
        return;
   
    //Update object and transform controller selection
    std::vector<int> ids;
    updateSelections(ids);

    //Move object and transform if needed
    if(transformController->inControl()) {
        glm::vec3 origin, direction;
        picker.calculateRay(&origin, &direction);

        if(_tMode == POSITION)
            updatePositionAdjustments(origin, direction);
        else if(_tMode == SCALE)
            updateScaleAdjustments(origin, direction);
    }
}

void MainEditor::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f,0.5f,0.5f,1.0f);

    glDepthRange(0.01, 1);
    renderer.beginObjectRender();
    renderer.renderObjects(camera);
    renderer.endObjectRender();

    glDepthRange(0.0, 0.01);
    transformController->render(camera, transformShader);
    glDepthRange(0,1);

    renderer.renderGUIs();

    renderer.endRender(window);
}

void MainEditor::gameLoop()
{
    timer.TimeInit();
    while(isRunning) {
        timer.FpsLimitInit();
        timer.calcDeltaTime();

        input();
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

void MainEditor::createCube()
{
    renderer.addCube(0,0,0, 0,0,0, 1,1,1);
    renderer.unselectAllObjects();
}

void MainEditor::deleteCubes()
{
    std::vector<unsigned int> selectedIDs = renderer.getSelectedIDs();
    for(unsigned int i = 0; i < selectedIDs.size(); i++) {
        renderer.deleteObject(selectedIDs[i]);
    }
    transformController->setControlling(false);
    transformController->setVisible(false);
}

void MainEditor::setTransfromMode(TransformMode mode)
{
    if(mode == POSITION)
        transformMode->setText("Mode: Position");
    if(mode == SCALE)
        transformMode->setText("Mode: Scale");

    _tMode = mode;
}