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

    camera.init(screenWidth, screenHeight);
    camera.setPosition(-1.0f, 0.0f, 2.0f);

    Cube* c = new Cube(0,0,-3,0,25,45,1.5,1.5,1.5);
    _objects.push_back(c);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = camera.getProjectionMatrix();

	staticShader.start();
	staticShader.getUniformLocations();

    for(GameObject* obj : _objects) {
        glm::mat4 model = Math::createTransformationMatrix(obj->getPosition(), obj->getRotation(), obj->getScale());
        glm::mat4 mvp = proj * view * model;

        staticShader.loadMVPMatrix(mvp);

        obj->render();
    }

    staticShader.stop();
    
    SDL_GL_SwapWindow(window);
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