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

        //configuring and sending light uniforms
        programManager->getMapProgram()->use();
        sun.resetDirection();
        sun.rotate(windowManager.getTime()*0.5, camera->getViewMatrix());
        sun.sendLightUniforms(programManager->getMapProgram());

        moon.resetDirection();
        moon.rotate(-windowManager.getTime()*0.5, camera->getViewMatrix());
        moon.sendLightUniforms(programManager->getMapProgram());

        programManager->getElementProgram()->use();
        sun.sendLightUniforms(programManager->getElementProgram());
        moon.sendLightUniforms(programManager->getElementProgram());

        //draw skybox
        glDepthMask(GL_FALSE);
        sky->draw(camera->getViewMatrix());
        glDepthMask(GL_TRUE);
        //grass->draw(camera->getViewMatrix());
        //draw map

        Map->draw(camera->getViewMatrix());

        //sky draw element -> will be called by draw map later
        //elementVect[0]->draw(camera->getViewMatrix());
        /*for(int i =0; i<Tools::nbSub+1; ++i){
            for(int j =0; j<Tools::nbSub+1; ++j){

                elementVect[i*(Tools::nbSub+1)+j]->draw(glm::scale(glm::translate(camera->getViewMatrix() , elementVect[i*(Tools::nbSub+1)+j]->position) , glm::vec3(0.1,0.1,0.1)));
            }
        }*/
        //addDOF();
        windowManager.swapBuffers();
        printErrors();

    }
    delete sky;
    delete Map;
    //delete factory;
   // delete grass;
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
        clearGl();

        GLuint frameBuffer;
        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

        glcustom::Texture * originalColor = new glcustom::Texture(Tools::windowWidth, Tools::windowHeight, nullptr , GL_RGB);
        originalColor->bind(GL_TEXTURE_2D);
        glFramebufferTexture2D(
                GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, originalColor->getM_id(), 0
        );



        glcustom::Texture * originalDepth = new glcustom::Texture(Tools::windowWidth, Tools::windowHeight, nullptr , GL_DEPTH_COMPONENT);
        /*
        originalDepth->bind(GL_TEXTURE_2D);

        glFramebufferTexture2D(
                GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, originalDepth->getM_id(), 0
        );

        originalDepth->debind(GL_TEXTURE_2D);
        */
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
            std::cerr << "framebuffer instancing failed " << std::endl;
        }


        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
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


        //round rock

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        //roundRock->draw(camera->getViewMatrix());


        //branche->draw(camera->getViewMatrix());


        //experienceRock->draw(camera->getViewMatrix());

        //feuillage->draw(camera->getViewMatrix());

        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        //roundRock2->draw(camera->getViewMatrix());

        //menirRock->draw(camera->getViewMatrix());

        //roundRock2->draw(camera->getViewMatrix());

        //skybox
        glDepthMask(GL_FALSE);
        test->draw(camera->getViewMatrix());
        glDepthMask(GL_TRUE);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        addDOF(originalColor, originalDepth);

        windowManager.swapBuffers();
        printErrors();

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

    /*
    GLuint frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    float * textureData;
    glcustom::Texture * testTexture = new glcustom::Texture(Tools::windowWidth, Tools::windowHeight, nullptr , GL_RGB);
    testTexture->bind(GL_TEXTURE_2D);
    glFramebufferTexture2D(
            GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, testTexture->getM_id(), 0
    );

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cerr << "framebuufer instancing failed " << std::endl;
    }
*/    //GLuint fbo1;
    //glGenBuffers()
    float * originalFBColor = new float[Tools::windowHeight * Tools::windowWidth *3];
    float * originalFBDepth = new float[Tools::windowHeight * Tools::windowWidth];
    float * newFB = new float[Tools::windowHeight * Tools::windowWidth*3];
    int zNear = 0, zFar = 500;
    float pixelDepth, CoCDiam, apperture, coefficient, focalLength, screenPos ;

    apperture = 2.0;
    screenPos = 10.0;
    focalLength = 5.0;
    coefficient = 1;


    glReadPixels(0, 0, Tools::windowWidth, Tools::windowHeight, GL_RGB, GL_FLOAT, originalFBColor);

    glReadPixels(0, 0, Tools::windowWidth, Tools::windowHeight, GL_DEPTH_COMPONENT, GL_FLOAT, originalFBDepth);

    /*
    for(int i = 0; i<Tools::windowHeight; i++){
        for(int j = 0; j<Tools::windowWidth; j++){
            pixelDepth = zNear*zFar / (zFar - originalFBDepth[i*Tools::windowHeight+j]*(zFar - zNear));
            CoCDiam = abs(
                    apperture
                    - coefficient * (
                            screenPos * (1.0 / focalLength - 1.0 / pixelDepth)
                            -1
                                                        )
            );

            uniformLightDistribution(CoCDiam, i, j, originalFBColor, newFB);

        }
    }
     */


    std::vector<glimac::ShapeVertex> vertices = {
            glimac::ShapeVertex(glm::vec3(-1,1,0), glm::vec3(0), glm::vec2(0,1)),
            glimac::ShapeVertex(glm::vec3(1,1,0), glm::vec3(0), glm::vec2(1,1)),
            glimac::ShapeVertex(glm::vec3(-1,-1,0), glm::vec3(0), glm::vec2(0,0)),
            glimac::ShapeVertex(glm::vec3(1,1,0), glm::vec3(0), glm::vec2(1,1)),
            glimac::ShapeVertex(glm::vec3(-1,-1,0), glm::vec3(0), glm::vec2(0,0)),
            glimac::ShapeVertex(glm::vec3(1,-1,0), glm::vec3(0), glm::vec2(1,0))
    };

    glcustom::VAO vao;
    glcustom::VBO vbo;
    vbo.fillBuffer(vertices);
    vao.fillBuffer(vertices, &vbo);

    glcustom::GPUProgram * p = programManager->getDOFProgram();

    p->use();
    text->bind(GL_TEXTURE_2D);
    p->sendUniformTextureUnit("uTexture0", 0);
    depth->bind(GL_TEXTURE_2D, GL_TEXTURE1);
    p->sendUniformTextureUnit("uTexture1", 1);
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao.debind();
    text->debind(GL_TEXTURE_2D);
    depth->debind(GL_TEXTURE_2D);



    delete[] originalFBColor;
    delete[] originalFBDepth;
    delete[] newFB;

}

void Application::uniformLightDistribution(float diam, int x, int y, float * originalColor, float *newColor) {
    int r = diam/2;
    float a = glm::pi<float>() * r * r ;
    float intensity = originalColor[x*Tools::windowHeight+y]/a;
    for(int i = -r; i< r; i ++){
        for(int j = -r; j< r; j ++){
            if( pow(i*i*j*j, 0.5) < r ){
                newColor[x*Tools::windowHeight+y] += intensity;
            }
        }
    }
}
