//
// Created by Lou Landry on 15/01/2018.
//


#include "Application.hpp"



void Application::initOpenGl() {
    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        //return EXIT_FAILURE; //handle exception
    }
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);
}

void Application::clearGl() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.7, 0.3, 0.2, 1);
}

Application::Application(const std::string &appPath) : windowManager(Tools::windowWidth, Tools::windowHeight, "BarrenLight"), programManager(nullptr){
    initOpenGl();
    programManager = new ProgramManager(appPath);
}

void Application::appLoop() {
    programManager->createPrograms();
    ProceduralObject testCube;
    testCube.createRenderObject(programManager->getTestProgram());
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e{};
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }
        glm::mat4 viewMatrixTest = glm::translate(glm::mat4(1.0), glm::vec3(0,0,-5));
        testCube.draw(viewMatrixTest);
        clearGl();
        windowManager.swapBuffers();

    }

}

void Application::printErrors() {
    GLuint error = glGetError();
    if(error != GL_NO_ERROR){
        std::cerr << glewGetErrorString(error) << std::endl;
    }
}

Application::~Application() {
 delete programManager;
}
