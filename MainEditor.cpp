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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    staticShader.init("Shaders/shader.vert", "Shaders/shader.frag");
    staticShader.bindAttributes();
    
    renderer.init(&staticShader);

    camera.init(screenWidth, screenHeight);
    camera.setPosition(0.0f, 0.0f, 3.0f);

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
    light3 = renderer.addDirectionalLight(1.0f,0.0f,-0.3f,   1.0f,1.0f,1.0f,     intensity);
}

void MainEditor::update()
{
    SDL_Event evnt;
    while(SDL_PollEvent(&evnt)) {
        switch(evnt.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_MOUSEMOTION:
            //TODO: Add mouselook
                inputManager.setMouseCoords(evnt.motion.xrel, evnt.motion.yrel);
                break;
            case SDL_KEYDOWN:
                inputManager.keyPressed(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                inputManager.keyReleased(evnt.key.keysym.sym);
                break;
        }
    }

    camera.update();

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
}

void MainEditor::render()
{
    renderer.beginRender();
    renderer.renderObjects(camera);
    renderer.endRender(window);
}

void MainEditor::gameLoop()
{
    _timer.TimeInit();
    while(isRunning) {
        _timer.FpsLimitInit();
        _timer.calcDeltaTime();
        update();
        render();

        _timer.CalculateFPS(true);
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