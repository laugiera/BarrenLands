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


    // Compute the MVP matrix from the light's point of view
    glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
    glm::mat4 depthModelMatrix = glm::mat4(1.0);
    glm::mat4 depthViewMatrix;
    glm::mat4 depthMVP;

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
        moon.rotate(-windowManager.getTime()*0.5, camera->getViewMatrix());
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

    ProceduralObject * tree = ElementManager::getInstance().createProceduralTree();
    tree->addInstance(glm::vec3(0,0,0), Color(1,1,0));
    tree->createRenderObject(programManager, textureManager);





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
        glcustom::FBO fbo;
        fbo.bind();
        glcustom::Texture originalColor = fbo.attachColorTexture(Tools::windowWidth, Tools::windowHeight);
        glcustom::Texture originalDepth = fbo.attachDepthTexture(Tools::windowWidth, Tools::windowHeight);
        fbo.checkComplete();
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


        std::vector<ProceduralObject *> elements = ElementManager::getInstance().getAllElements();
        for (ProceduralObject * el : elements){
            el->draw(camera->getViewMatrix());
        }


        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        //skybox
        glDepthMask(GL_FALSE);
        test->draw(camera->getViewMatrix());
        glDepthMask(GL_TRUE);



        //le rendu final est là dedans pour mes test pour l'instant
        addDOF(&originalColor, &originalDepth);

        windowManager.swapBuffers();
        printErrors();

        //glDeleteFramebuffers(1, &frameBuffer);

    }
    //delete testObject;

    //delete testRock;

    //delete roundRock;
    delete test;

    //delete grass;
    //delete branche;

    //delete experienceRock;

    //delete feuillage;
    //delete color;

}

void Application::addDOF(glcustom::Texture *text, glcustom::Texture *depth) {


    float * originalFBColor = new float[Tools::windowHeight * Tools::windowWidth *3];
    float * originalFBDepth = new float[Tools::windowHeight * Tools::windowWidth];
    float * newFB = new float[Tools::windowHeight * Tools::windowWidth*3];
    float zNear = 0.1, zFar = 2000;
    float pixelDepth, CoCDiam, apperture, coefficient, focalLength, screenPos ;

    apperture = 2.0;
    screenPos = 10.0;
    focalLength = 5.0;
    coefficient = 1;


    glReadPixels(0, 0, Tools::windowWidth, Tools::windowHeight, GL_RGB, GL_FLOAT, originalFBColor);

    glReadPixels(0, 0, Tools::windowWidth, Tools::windowHeight, GL_DEPTH_COMPONENT, GL_FLOAT, originalFBDepth);

    /*
    for(int i = 0; i<Tools::windowHeight; i++){
        for(int j = 0; j<Tools::windowWidth*3; j += 3){
            pixelDepth = zNear*zFar / (zFar - originalFBDepth[i*Tools::windowWidth+j/3]*(zFar - zNear));
            CoCDiam = abs(
                    apperture
                    - coefficient * (
                            screenPos * (1.0 / focalLength - 1.0 / pixelDepth)
                            -1
                                                        )
            );

            uniformLightDistribution(CoCDiam, i, j/3, originalFBColor, newFB);

        }
    }
     */

    /* //WORKS
    for (int i = 0; i<Tools::windowHeight * Tools::windowWidth *3; i+=3){
        if(originalFBDepth[i/3] == 1){
            newFB[i] = originalFBColor[i] + 0.3;
            newFB[i+1] = originalFBColor[i+1] + 0.3;
            newFB[i+2] = originalFBColor[i+2] + 0.3;
        } else {
            newFB[i] = originalFBColor[i];
            newFB[i+1] = originalFBColor[i+1];
            newFB[i+2] = originalFBColor[i+2];
        }
    }
     */


    text = new glcustom::Texture(Tools::windowWidth, Tools::windowHeight, newFB, GL_RGB);
    std::vector<glcustom::Texture *> texts = { text, depth};

    RenderScreen screen(programManager->getDOFProgram(), texts);
    screen.render();

    delete[] originalFBColor;
    delete[] originalFBDepth;
    delete[] newFB;


}

void Application::uniformLightDistribution(float diam, int x, int y, float * originalColor, float *newColor) {
    int r = diam/2;
    float a = glm::pi<float>() * r * r ;
    float rIntensity = originalColor[x*Tools::windowWidth *3 + y] / a;
    float gIntensity = originalColor[x*Tools::windowWidth *3 + y+1] / a;
    float bIntensity = originalColor[x*Tools::windowWidth *3 + y+2] /a;
    for(int i = -r; i< r; i ++){
        for(int j = -r; j< r; j ++){
            if( pow(i*i*j*j, 0.5) < r ){
                newColor[x*Tools::windowWidth*3 +y ] += rIntensity;
                newColor[x*Tools::windowWidth*3 +y +1] += gIntensity;
                newColor[x*Tools::windowWidth*3 +y +2] += bIntensity;
            }
        }
    }
}

