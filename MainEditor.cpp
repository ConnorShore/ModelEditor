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
}

void MainEditor::update()
{
    SDL_Event evnt;
    while(SDL_PollEvent(&evnt)) {
        switch(evnt.type) {
            case SDL_QUIT:
                exit(0);
                break;
        }
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