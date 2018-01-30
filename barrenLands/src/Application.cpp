//
// Created by Lou Landry on 15/01/2018.
//
#define GLEW_STATIC
#include <RoundRock.hpp>
#include <ExperienceRock.hpp>
#include "ProceduralGrass.hpp"
#include "ProceduralBranche.hpp"
#include "ProceduralFeuillage.hpp"
#include "ProceduralTree.hpp"
#include "Application.hpp"


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

    //fbo
    glm::mat4 biasMatrix(
            0.5, 0.0, 0.0, 0.0,
            0.0, 0.5, 0.0, 0.0,
            0.0, 0.0, 0.5, 0.0,
            0.5, 0.5, 0.5, 1.0
    );
    glm::mat4 depthBiasMVP;
    // Compute the MVP matrix from the light's point of view
    glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
    glm::mat4 depthModelMatrix = glm::mat4(1.0);
    glm::mat4 depthViewMatrix;
    glm::mat4 depthMVP;
    
    glcustom::FBO fboShadow;
    fboShadow.bind();
    glcustom::Texture lightDepth = fboShadow.attachDepthTexture(Tools::windowWidth, Tools::windowHeight);
    textureManager->addTexture(&lightDepth,"shadowMap");
    fboShadow.checkComplete();
    fboShadow.debind();


    ElementManager::getInstance().createAllElements();

    //initialization of lights
    Light sun = Light(1,"Sun",glm::vec3(0.5,0.1,0));
    sun.addLightUniforms(programManager->getMapProgram());
    sun.addLightUniforms(programManager->getElementProgram());
    Light moon = Light(1,"Moon",glm::vec3(0,0.1,0.5));
    moon.addLightUniforms(programManager->getMapProgram());
    moon.addLightUniforms(programManager->getElementProgram());

    //intialization of map
    ProceduralMap * Map = new ProceduralMap();
    Map->createRenderObject(programManager, textureManager);

    //initilization of skybox
    SkyboxObject * sky = new SkyboxObject();
    sky -> createRenderObject(programManager, textureManager);


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
                camera->zoom(-Tools::speed);
            else if (e.wheel.y == -1)
                camera->zoom(Tools::speed);
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
        /**************LIGHT DETH BUFFER***********/
        fboShadow.bind();
        depthViewMatrix = glm::lookAt(glm::vec3(sun.getDirection().x,sun.getDirection().y,sun.getDirection().z),
                                                glm::vec3(0,0,0),
                                                glm::vec3(0,1,0));
        depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;
        depthBiasMVP = biasMatrix*depthMVP;

        //configuring and sending light uniforms
        programManager->getMapProgram()->use();
        programManager->getMapProgram()->sendUniformMat4("uDepthMVP",depthBiasMVP);

        sun.resetDirection();
        sun.rotate(windowManager.getTime(), camera->getViewMatrix());
        sun.sendLightUniforms(programManager->getMapProgram());

        moon.resetDirection();
        moon.rotate(-windowManager.getTime(), camera->getViewMatrix());
        moon.sendLightUniforms(programManager->getMapProgram());

        programManager->getElementProgram()->use();
        programManager->getElementProgram()->sendUniformMat4("uDepthMVP",depthBiasMVP);
        sun.sendLightUniforms(programManager->getElementProgram());
        moon.sendLightUniforms(programManager->getElementProgram());

        //render the map with light point of view
        Map->draw(depthBiasMVP);
        fboShadow.debind();
        //fboShadow.attachDepthTexture(Tools::windowWidth, Tools::windowHeight);

        /***************MAP FRAME BUFFER****************/
        //draw skybox
        glDepthMask(GL_FALSE);
        sky->draw(camera->getViewMatrix());
        glDepthMask(GL_TRUE);

        //draw map
        Map->draw(camera->getViewMatrix());

        /********************************************/

        //addDOF(&originalColor, &originalDepth, fbo);
        windowManager.swapBuffers();
        printErrors();

    }
    delete sky;
    delete Map;
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
    ElementManager::getInstance().createAllElements();

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

    //ProceduralObject * testRock = new ArchedRock();
    //testRock->createRenderObject(programManager, textureManager);




    //test RoundRock
    //ProceduralObject * menirRock = new MenirRock();
    //menirRock->createRenderObject(programManager, textureManager);

    //ProceduralObject * roundRock2 = new RoundRock();
    //roundRock2->createRenderObject(programManager, textureManager);
/*
    ProceduralObject * roundRock3 = new RoundRock();
    roundRock3->createRenderObject(programManager, textureManager);
*/
    //test Grass
    //ProceduralObject * grass = new ProceduralGrass(glm::vec3(0,0,0));
    //grass->createRenderObject(programManager, textureManager);

    //test Branche
    //ProceduralObject * branche = new ProceduralBranche();
    //branche->createRenderObject(programManager, textureManager);

    //ProceduralObject * feuillage = new ProceduralFeuillage();
    //Color * color = new Color(0,1,0);
    //feuillage->createRenderObject(programManager, textureManager, color);

    //ProceduralObject * feuillage = new ProceduralTree();
    //feuillage->createRenderObject(programManager, textureManager);


    //ProceduralObject * experienceRock = new ExperienceRock();
    //experienceRock->createRenderObject(programManager, textureManager);

    //ProceduralObject * tree = ElementManager::getInstance().createProceduralTree();
    //tree->addInstance(glm::vec3(0,0,0), Color(1,1,0));
    //tree->createRenderObject(programManager, textureManager);

    ProceduralObject * rock = ElementManager::getInstance().createProceduralRock("");
    rock->addInstance(glm::vec3(0,0,0), Color(1,1,0));
    rock->createRenderObject(programManager, textureManager);

    glcustom::FBO fbo;
    fbo.bind();
    glcustom::Texture originalColor = fbo.attachColorTexture(Tools::windowWidth, Tools::windowHeight);
    glcustom::Texture originalDepth = fbo.attachDepthTexture(Tools::windowWidth, Tools::windowHeight);
    fbo.checkComplete();


    bool done = false;
    int rightPressed = 0;
    camera->moveFront(-5);
    while(!done) {
        // Event loop:
        SDL_Event e{};
        while(windowManager.pollEvent(e)) {
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_LEFT) {
                    camera->moveLeft(Tools::speed);
                } else if (e.key.keysym.sym == SDLK_RIGHT) {
                    camera->moveLeft(-Tools::speed);
                } else if (e.key.keysym.sym == SDLK_UP) {
                    camera->moveFront(Tools::speed);
                } else if (e.key.keysym.sym == SDLK_DOWN) {
                    camera->moveFront(-Tools::speed);
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
                camera->zoom(-Tools::speed);
            else if (e.wheel.y == -1)
                camera->zoom(Tools::speed);
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

        //setting up fbo and linking color and depth buffer
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


        std::vector<ProceduralObject *> elements = ElementManager::getInstance().getAllElements();
        for (ProceduralObject * el : elements){
            el->draw(camera->getViewMatrix());
        }

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


        //roundRock->draw(camera->getViewMatrix());


        //branche->draw(camera->getViewMatrix());

        //experienceRock->draw(camera->getViewMatrix());

        //feuillage->draw(camera->getViewMatrix());

        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        //skybox
        glDepthMask(GL_FALSE);
        test->draw(camera->getViewMatrix());
        glDepthMask(GL_TRUE);



        //le rendu final est là dedans pour mes test pour l'instant
        addDOF(&originalColor, &originalDepth, fbo);

        windowManager.swapBuffers();
        printErrors();

        //glDeleteFramebuffers(1, &frameBuffer);

    }
    delete test;


}

void Application::addDOF(glcustom::Texture *beauty, glcustom::Texture *depth, glcustom::FBO &fbo) {

    //glcustom::Texture initialDepth = *depth;
    // std::vector<glcustom::Texture *> texts = { beauty, depth};

    glcustom::Texture blur = fbo.attachColorTexture(Tools::windowWidth, Tools::windowHeight);
    fbo.attachDepthTexture(Tools::windowWidth, Tools::windowHeight);

    std::vector<glcustom::Texture *> texts = { beauty, depth };
    RenderScreen screenColorCorrec(programManager->getGammaProgram(), texts);
    screenColorCorrec.render(&fbo);


    texts.clear();
    texts.push_back(&blur);

    RenderScreen screenBlur(programManager->getBlurProgram(), texts);
    programManager->getBlurProgram()->use();
    programManager->getBlurProgram()->sendUniform1i("uSampleCount", 2);
    programManager->getBlurProgram()->sendUniformVec3("uDirection", glm::vec3(0,1,0));
    screenBlur.render(&fbo);


    programManager->getBlurProgram()->sendUniformVec3("uDirection", glm::vec3(1,0,0));
    screenBlur.render(&fbo);


    texts.push_back(beauty);
    texts.push_back(depth);
    RenderScreen screenDOF(programManager->getDOFProgram(), texts);
    screenDOF.render();



}

