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

Application::Application(const std::string &appPath) : windowManager(Tools::windowWidth, Tools::windowHeight, "BarrenLands"),
                                                       programManager(nullptr),
                                                       camera(nullptr)
{
    initOpenGl();
    programManager = new ProgramManager(appPath);
    camera = new CameraManager();
}

void Application::appLoop() {
    programManager->createPrograms();
    ProceduralObject testCube;
    testCube.createRenderObject(programManager->getTestProgram());
    bool done = false;
    int rightPressed = 0;
    while(!done) {
        // Event loop:
        SDL_Event e{};
        while(windowManager.pollEvent(e)) {
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_LEFT) {
                    camera->moveLeft(1.0);
                } else if (e.key.keysym.sym == SDLK_RIGHT) {
                    camera->moveLeft(-1.0);
                } else if (e.key.keysym.sym == SDLK_UP) {
                    camera->moveFront(1.0);
                } else if (e.key.keysym.sym == SDLK_DOWN) {
                    camera->moveFront(-1.0);
                }
                if (e.key.keysym.sym == SDLK_v) {
                    if(camera->getChoice() == 0){
                        camera->setChoice(1);
                    }
                    else{
                        camera->setChoice(0);
                    }
                }
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_RIGHT) {
                    rightPressed = 1;
                }
            } else if (e.wheel.y == 1)
                camera->zoom(-1);
            else if (e.wheel.y == -1)
                camera->zoom(1);
            else if (e.type == SDL_MOUSEBUTTONUP) {
                if (e.button.button == SDL_BUTTON_RIGHT) {
                    rightPressed = 0;
                }
            } else if (e.type == SDL_MOUSEMOTION && rightPressed == 1) {
                camera->rotateLeft(e.motion.xrel);
                camera->rotateUp(e.motion.yrel);
            }
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }
        clearGl();
        testCube.draw(camera->getViewMatrix());
        //testCube.draw(glm::translate(glm::mat4(1), glm::vec3(0,0,-50)));
        windowManager.swapBuffers();
        printErrors();

    }

}

void Application::printErrors() {
    GLuint error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << glewGetErrorString(error) << std::endl;
    }
}

Application::~Application() {
 delete programManager;
}
