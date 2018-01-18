//
// Created by Lou Landry on 15/01/2018.
//

#include "Application.hpp"





Application::Application(const glimac::FilePath &appPath) : windowManager(Tools::windowWidth, Tools::windowHeight, "BarrenLands"),
                                                            programManager(nullptr),
                                                            camera(nullptr),
                                                            textureManager(nullptr),
                                                            noiseManager(nullptr)
{
    initOpenGl();
    textureManager = new TextureManager(appPath);
    programManager = new ProgramManager(appPath);
    camera = new CameraManager();
    noiseManager = &NoiseManager::getInstance();
}

int Application::initOpenGl() {
    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE; //handle exception
    }
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);
}

void Application::clearGl() {
    //glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.7, 0.3, 0.2, 1);
}

void Application::appLoop() {
    programManager->createPrograms();

    Light light = Light(1,"Test",glm::vec3(0.5,0.1,0));
    light.addLightUniforms(programManager->getLightProgram());

    //autres lights ajoutées aux bons programs

    ProceduralMap testMap(noiseManager);
    testMap.createRenderObject(programManager, textureManager);

    SkyboxObject * test = new SkyboxObject();
    test -> createRenderObject(programManager, textureManager);

    /*ElementFactory* factory = new ElementFactory(); //Décommenter "POSITION" dans PROCEDURALOBJECT
    std::vector<ProceduralObject*> elementVect;
    for(int i =0; i<Tools::nbSub+1; ++i){
        for(int j =0; j<Tools::nbSub+1; ++j){
            elementVect.push_back(factory->createProceduralObject());
            elementVect[i*(Tools::nbSub+1)+j]->createRenderObject(programManager, textureManager);
            elementVect[i*(Tools::nbSub+1)+j]->position = testMap.getVertices(i,j).position;
        }
    }*/


    bool done = false;
    int rightPressed = 0;
    camera->moveFront(Tools::speed, testMap.getVerticesTab());
    while(!done) {
        // Event loop:
        SDL_Event e{};
        while(windowManager.pollEvent(e)) {
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_LEFT) {
                    camera->moveLeft(Tools::speed, testMap.getVerticesTab());
                } else if (e.key.keysym.sym == SDLK_RIGHT) {
                    camera->moveLeft(-Tools::speed, testMap.getVerticesTab());
                } else if (e.key.keysym.sym == SDLK_UP) {
                    camera->moveFront(Tools::speed, testMap.getVerticesTab());
                } else if (e.key.keysym.sym == SDLK_DOWN) {
                    camera->moveFront(-Tools::speed, testMap.getVerticesTab());
                } else if (e.key.keysym.sym == SDLK_v) {
                    if(camera->getChoice() == 0){
                        camera->setChoice(1);
                    }
                    else{
                        camera->setChoice(0);
                    }
                } else if(e.key.keysym.sym == SDLK_b){
                    programManager->reloadPrograms();
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

        programManager->getLightProgram()->use();
        light.resetDirection();
        light.rotate(windowManager.getTime(),camera->getViewMatrix());
        light.sendLightUniforms(programManager->getLightProgram());

        glDepthMask(GL_FALSE);
        test->draw(camera->getViewMatrix());
        glDepthMask(GL_TRUE);

        //elementVect[0]->draw(camera->getViewMatrix());
        testMap.draw(camera->getViewMatrix());

        /*for(int i =0; i<Tools::nbSub+1; ++i){
            for(int j =0; j<Tools::nbSub+1; ++j){

                elementVect[i*(Tools::nbSub+1)+j]->draw(glm::scale(glm::translate(camera->getViewMatrix() , elementVect[i*(Tools::nbSub+1)+j]->position) , glm::vec3(0.1,0.1,0.1)));
            }
        }*/

        windowManager.swapBuffers();
        printErrors();

    }
    delete test;
    //delete factory;

}

void Application::printErrors() {
    GLuint error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "code " << error << ":" << glewGetErrorString(error)  << std::endl;
    }
}

Application::~Application() {
 delete programManager;
}

const glimac::SDLWindowManager &Application::getWindowManager() const {
    return windowManager;
}

void Application::testInterface() {
    textureManager->createTextures();
    programManager->createPrograms();

    Light light = Light(1,"Test",glm::vec3(0.5,0.1,0));
    light.addLightUniforms(programManager->getLightProgram());

    //----> Edit with the class you want to test :
    ProceduralObject * testObject = new ProceduralObject();
    //---->TestProgram uses TestShader with texture support
    testObject->createRenderObject(programManager, textureManager);

    SkyboxObject * test = new SkyboxObject();
    test -> createRenderObject(programManager, textureManager);

    bool done = false;
    int rightPressed = 0;
    camera->moveFront(-5);
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
                } else if (e.key.keysym.sym == SDLK_v) {
                    if(camera->getChoice() == 0){
                        camera->setChoice(1);
                    }
                    else{
                        camera->setChoice(0);
                    }
                } else if(e.key.keysym.sym == SDLK_b){
                    programManager->reloadPrograms();
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
        glDepthFunc(GL_LEQUAL);

        programManager->getLightProgram()->use();
        light.resetDirection();
        light.rotate(windowManager.getTime(),camera->getViewMatrix());
        light.sendLightUniforms(programManager->getLightProgram());

        testObject->draw(camera->getViewMatrix());

        glDepthMask(GL_FALSE);
        test->draw(camera->getViewMatrix());
        glDepthMask(GL_TRUE);



        windowManager.swapBuffers();


        printErrors();

    }
  delete testObject;
  delete test;
}
