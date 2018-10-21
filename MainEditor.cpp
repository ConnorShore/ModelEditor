#include "MainEditor.h"
#include <string>
#include <iostream>
#include <glm/glm.hpp>

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

    staticShader.init("Shaders/shader.vert", "Shaders/shader.frag");
    staticShader.bindAttributes();
    
    renderer.init(&staticShader);

    camera.init(screenWidth, screenHeight);
    camera.setPosition(-1.0f, 0.0f, 2.0f);

    renderer.addCube(0,0,-3,0,25,45,1.5,1.5,1.5);
    renderer.addCube(-10,-3,-8,0,0,0,1.0, 4.0, 1.5);
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
}

void MainEditor::render()
{
    renderer.beginRender();
    renderer.renderObjects(camera);
    renderer.endRender(window);
}

void MainEditor::gameLoop()
{
    while(isRunning) {
        update();
        render();
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