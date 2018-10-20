#include "MainEditor.h"
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include "Math.h"

GLuint vaoID = 0;
GLuint vboID = 0;
GLuint vioID = 0;

float vertices[] = {
    -1.0f, -1.0f, 1.0f,        1.0f, 1.0f, 1.0f, 1.0f, //front bottom left  [0]
    1.0f, -1.0f, 1.0f,         1.0f, 1.0f, 0.0f, 1.0f, //front bottom right [1]
    1.0f, 1.0f, 1.0f,          1.0f, 0.0f, 1.0f, 1.0f, //front top right    [2]
    -1.0f, 1.0f, 1.0f,         0.0f, 1.0f, 1.0f, 1.0f, //front top left     [3]

    -1.0f, -1.0f, -1.0f,       1.0f, 0.0f, 0.0f, 1.0f, //back bottom left   [4]
    1.0f, -1.0f, -1.0f,        0.0f, 1.0f, 0.0f, 1.0f, //back bottom right  [5]
    1.0f, 1.0f, -1.0f,         0.0f, 0.0f, 1.0f, 1.0f, //back top right     [6]
    -1.0f, 1.0f, -1.0f,        0.5f, 1.0f, 0.5f, 1.0f //back top left      [7]
};

unsigned int indices[] = {
    0,1,2,3,    //front
    1,5,6,2,    //right
    4,5,6,7,     //back
    4,0,3,7,     //left
    3,2,6,7,     //top
    0,1,5,4     //bottom
};

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

    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboID);
    glGenBuffers(1, &vioID);

    glBindVertexArray(vaoID);

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vioID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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

    glm::vec3 pos(1.0f, 0.0f, -3.0f);
    glm::vec3 rot(0.0f, 25.0f, 45.0f);
    glm::vec3 scale(1.25f);

    glm::mat4 model = Math::createTransformationMatrix(pos, rot, scale);
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = camera.getProjectionMatrix();
    glm::mat4 mvp = proj * view * model;

	staticShader.start();
	staticShader.getUniformLocations();
    staticShader.loadMVPMatrix(mvp);

    glBindVertexArray(vaoID);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, 0);

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
    glDeleteVertexArrays(1, &vaoID);
    glDeleteBuffers(1, &vboID);
    glDeleteBuffers(1, &vioID);
    SDL_DestroyWindow(window);
}

void MainEditor::run()
{
    init();
    gameLoop();
    cleanUp();
}