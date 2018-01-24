//
// Created by Lou Landry on 15/01/2018.
//
#define GLEW_STATIC
#include <RoundRock.hpp>
#include "ProceduralGrass.hpp"
#include "Application.hpp"
#include <SharpRock.hpp>
#include <ArchedRock.hpp>


/**
 * Constructs the App with the SDL2 WindowManager
 * @param appPath
 */
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

Application::~Application() {
    delete programManager;
    delete textureManager;
    //delete windowManager; ->compiler says cannot delete type glimac::SDLWindowManager

}

/**
 * Initializes the OpenGL Context and glew for OpenGL 3+ support
 * throws std::runtime
 */
void Application::initOpenGl() {
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl; //error message has a weird ass format
        throw std::runtime_error("Glew could not be initialized"); //handle exception
    }
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    //OpenGL initialization
    glEnable(GL_DEPTH_TEST);
}

/**
 * Render Loop related OpenGl Actions.
 * Mainly Buffer clearing
 */
void Application::clearGl() {
    //clearing of color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //setting background color
    glClearColor(0.7, 0.3, 0.2, 1);

    //depth handling for the skybox
    glDepthFunc(GL_LEQUAL);
}

/**
 * Final Application Loop
 * Handles initialization, SDL event loop and Rendering loop
 */
void Application::appLoop() {
    //creation of GPU Programs
    programManager->createPrograms();

    //initialization of lights
    Light sun = Light(1,"Sun",glm::vec3(0.7,0.1,0));
    sun.addLightUniforms(programManager->getMapProgram());
    sun.addLightUniforms(programManager->getElementProgram());
    Light moon = Light(1,"Moon",glm::vec3(0,0.1,0.7));
    moon.addLightUniforms(programManager->getMapProgram());
    moon.addLightUniforms(programManager->getElementProgram());

    //intialization of map
    ProceduralMap * Map = new ProceduralMap();
    Map->createRenderObject(programManager, textureManager);

    //initilization of skybox
    SkyboxObject * sky = new SkyboxObject();
    sky -> createRenderObject(programManager, textureManager);

    ProceduralObject * grass = new ProceduralGrass(glm::vec3(0,0,0));
    grass->createRenderObject(programManager, textureManager);

    /*ElementFactory* factory = new ElementFactory(); //Décommenter "POSITION" dans PROCEDURALOBJECT
    std::vector<ProceduralObject*> elementVect;
    for(int i =0; i<Tools::nbSub+1; ++i){
        for(int j =0; j<Tools::nbSub+1; ++j){
            elementVect.push_back(factory->createProceduralObject());
            elementVect[i*(Tools::nbSub+1)+j]->createRenderObject(programManager, textureManager);
            elementVect[i*(Tools::nbSub+1)+j]->position = Map->getVertices(i,j).position;
        }
    }*/


    bool done = false;
    int rightPressed = 0;
    camera->moveFront(Tools::speed, Map->getVertices());
    while(!done) {
        // Event loop:
        SDL_Event e{};
        while(windowManager.pollEvent(e)) {
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_z) { // Z
                    camera->moveFront(Tools::speed, Map->getVertices());
                } else if (e.key.keysym.sym == SDLK_s) { // S
                    camera->moveFront(-Tools::speed, Map->getVertices());
                }
                if (e.key.keysym.sym == SDLK_q) { // Q
                    camera->moveLeft(Tools::speed, Map->getVertices());
                } else if (e.key.keysym.sym == SDLK_d) { // D
                    camera->moveLeft(-Tools::speed, Map->getVertices());
                }
                if (e.key.keysym.sym == SDLK_UP) {
                    camera->moveFront(Tools::speed, Map->getVertices());
                } else if (e.key.keysym.sym == SDLK_DOWN) {
                    camera->moveFront(-Tools::speed, Map->getVertices());
                }
                if (e.key.keysym.sym == SDLK_LEFT) {
                    camera->rotateLeft(-Tools::speed);
                } else if (e.key.keysym.sym == SDLK_RIGHT) {
                    camera->rotateLeft(Tools::speed);
                }
                if (e.key.keysym.sym == SDLK_v) {
                    if (camera->getChoice() == 0) {
                        camera->setChoice(1);
                    } else {
                        camera->setChoice(0);
                    }
                } else if (e.key.keysym.sym == SDLK_b) {
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

        //configuring and sending light uniforms
        programManager->getMapProgram()->use();
        sun.resetDirection();
        sun.rotate(windowManager.getTime(), camera->getViewMatrix());
        sun.sendLightUniforms(programManager->getMapProgram());

        moon.resetDirection();
        moon.rotate(-windowManager.getTime(), camera->getViewMatrix());
        moon.sendLightUniforms(programManager->getMapProgram());

        programManager->getElementProgram()->use();
        sun.sendLightUniforms(programManager->getElementProgram());
        moon.sendLightUniforms(programManager->getElementProgram());

        //draw skybox
        glDepthMask(GL_FALSE);
        sky->draw(camera->getViewMatrix());
        glDepthMask(GL_TRUE);
        grass->draw(camera->getViewMatrix());
        //draw map

        Map->draw(camera->getViewMatrix());

        //sky draw element -> will be called by draw map later
        //elementVect[0]->draw(camera->getViewMatrix());
        /*for(int i =0; i<Tools::nbSub+1; ++i){
            for(int j =0; j<Tools::nbSub+1; ++j){

                elementVect[i*(Tools::nbSub+1)+j]->draw(glm::scale(glm::translate(camera->getViewMatrix() , elementVect[i*(Tools::nbSub+1)+j]->position) , glm::vec3(0.1,0.1,0.1)));
            }
        }*/

        windowManager.swapBuffers();
        printErrors();

    }
    delete sky;
    delete Map;
    //delete factory;
    delete grass;

}

/**
 * Print OpenGL Errors
 */
void Application::printErrors() {
    GLuint error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "code " << error << ":" << glewGetErrorString(error)  << std::endl;
    }
}


/**
 * Get a pointer on the SDL2 WindowManager
 * @return
 */
const glimac::SDLWindowManager &Application::getWindowManager() const {
    return windowManager;
}

/**
 * Test Loop : can be used instead of AppLoop to display an interface optimiezd
 * for testing the geometry creation and texture or color ajustement on Procedural Objects in development phase
 */
void Application::testInterface() {
    //textureManager->createTextures();
    programManager->createPrograms();

    //initialization of lights
    Light sun = Light(1,"Sun",glm::vec3(0.5,0.1,0));
    sun.addLightUniforms(programManager->getMapProgram());
    sun.addLightUniforms(programManager->getElementProgram());
    Light moon = Light(1,"Moon",glm::vec3(0,0.1,0.5));
    moon.addLightUniforms(programManager->getMapProgram());
    moon.addLightUniforms(programManager->getElementProgram());

    /********

    ----> Edit with the class you want to test :
    ----> TestProgram uses TestShader with texture support

     Example :

    ProceduralObject * testObject = new ProceduralObject();
    testObject->createRenderObject(programManager, textureManager);

     ********/

    //test skybox
    SkyboxObject * test = new SkyboxObject();
    test -> createRenderObject(programManager, textureManager);

    //test sea

    //ProceduralObject * testRock = new SharpRock();
    //testRock->createRenderObject(programManager, textureManager);

    ProceduralObject * testRock = new ArchedRock();
    testRock->createRenderObject(programManager, textureManager);




    //test RoundRock
    ProceduralObject * menirRock = new MenirRock();
    menirRock->createRenderObject(programManager, textureManager);

    ProceduralObject * roundRock2 = new RoundRock();
    roundRock2->createRenderObject(programManager, textureManager);
/*
    ProceduralObject * roundRock3 = new RoundRock();
    roundRock3->createRenderObject(programManager, textureManager);
*/
    //test Grass
    ProceduralObject * grass = new ProceduralGrass(glm::vec3(0,0,0));
    grass->createRenderObject(programManager, textureManager);


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

        //configuring and sending light uniforms
        programManager->getMapProgram()->use();
        sun.resetDirection();
        sun.rotate(windowManager.getTime(), camera->getViewMatrix());
        sun.sendLightUniforms(programManager->getMapProgram());

        moon.resetDirection();
        moon.rotate(-windowManager.getTime(), camera->getViewMatrix());
        moon.sendLightUniforms(programManager->getMapProgram());

        programManager->getElementProgram()->use();
        sun.sendLightUniforms(programManager->getElementProgram());
        moon.sendLightUniforms(programManager->getElementProgram());



        /******
        Example : testObject->draw(camera->getViewMatrix());
         ******/

        //sharp rock

        //testRock->draw(camera->getViewMatrix());



        //round rock

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        //roundRock->draw(camera->getViewMatrix());


        grass->draw(camera->getViewMatrix());

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        //roundRock2->draw(camera->getViewMatrix());

        menirRock->draw(camera->getViewMatrix());

        //roundRock2->draw(camera->getViewMatrix());

        //skybox
        glDepthMask(GL_FALSE);
        test->draw(camera->getViewMatrix());
        glDepthMask(GL_TRUE);

        windowManager.swapBuffers();
        printErrors();

    }
    //delete testObject;

    delete testRock;
    //delete roundRock;
    delete test;
    delete grass;

}
