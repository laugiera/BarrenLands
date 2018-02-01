//
// Created by Lou Landry on 15/01/2018.
//
#define GLEW_STATIC
#include <RoundRock.hpp>
#include <ExperienceRock.hpp>
//#include <SDL_mixer.h>
#include "ProceduralGrass.hpp"
#include "ProceduralBranche.hpp"
#include "ProceduralFeuillage.hpp"
#include "ProceduralTree.hpp"
#include "Application.hpp"

enum {
    CONTINUE, LOAD, SAVE, MAINMENU, QUIT
};

int Application::init_thread( void *data ) {

    textureManager = new TextureManager();
    programManager = new ProgramManager();
    camera = new CameraManager();
    return 0;
}
/**
 * Constructs the App with the SDL2 WindowManager
 * @param appPath
 */
Application::Application(const glimac::FilePath &appPath) : windowManager(Tools::windowWidth, Tools::windowHeight, "BarrenLands"),
                                                            programManager(nullptr),
                                                            camera(nullptr),
                                                            textureManager(nullptr) {
    initOpenGl();
    SDL_Init(SDL_INIT_AUDIO);
    /*SDL_Thread *thread;
    int threadReturnValue;
    printf("\nSimple SDL_CreateThread test:");

     //Simply create a thread
    thread = SDL_CreateThread(&init_thread, "init_thread", (void *) NULL);

    if (NULL == thread) {
        printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
    } else {
        SDL_WaitThread(thread, &threadReturnValue);
        printf("\nThread returned value: %d", threadReturnValue);
    }
*/
    init_thread((void *) NULL);
}
/**
 *
 * @param fileName
 * @return
 */
void Application::load(const std::string & fileName){
    try{
        std::vector<std::string> content = FileHelper::getContent(fileName);
        if(content.size() != 7)
           throw std::runtime_error("Bad init file");
        glm::vec3 cameraPos = glm::vec3(
                std::stof(content[0]),
                std::stof(content[1]),
                std::stof(content[2])
        );
        camera->setPosition(cameraPos);
        float phi = std::stof(content[3]);
        float theta = std::stof(content[4]);
        camera->rotateLeft(phi);
        camera->rotateUp(theta);
        lightRotation = std::stof(content[5]);

        float seed = std::stof(content[6]);
        //float seed = 127;
        NoiseManager::getInstance().setSeed(seed);
    }catch(std::runtime_error e){
        throw e;
    }

}
/**
 * save
 * @param fileName
 * @return
 */
void Application::save(){
    try{
        std::vector<std::string> content;
        glm::vec3 cameraPos = camera->getPosition();
        content.push_back(std::to_string(cameraPos.x));
        content.push_back(std::to_string(cameraPos.y));
        content.push_back(std::to_string(cameraPos.z));
        content.push_back("0"); //phi
        content.push_back("0"); //theta
        content.push_back(std::to_string(lightRotation));
        content.push_back(std::to_string(NoiseManager::getInstance().getSeed()));

        //FileHelper::updateFile()

    }catch(std::runtime_error e){
        throw e;
    }

}

Application::~Application() {
    ElementManager::ResetInstance();
    NoiseManager::ResetInstance();
    delete programManager;
    delete textureManager;
    std::cout << "delete texture manager ok" <<std::endl;
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
 * MainMenu()
 *
 * @return
 */
int Application::mainMenu(){

    int i;
    int srfIdx=0;
    int loop1 = 1;
    int menuIdx = 0;

    //SOUND

    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;

    SDL_LoadWAV("sounds/menu.wav", &wavSpec, &wavBuffer, &wavLength);

    // open audio device
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    // play audio
    int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);


    //show the image cube with initial image
    std::vector<glcustom::Texture *> textures;
    RenderScreen screen = RenderScreen(programManager->getTexture2DProgram(), textures);

    std::string qualifier = "menuSeed";
    screen.setTexture(textureManager->getRandomTexture(qualifier+std::to_string(1)));

    bool stateChanged=false;
    while (loop1)
    {

        //Update Screen
        //update texture from table
        if(stateChanged){
            screen.setTexture(textureManager->getRandomTexture(qualifier+std::to_string(menuIdx+1)));
            stateChanged= false;
        }

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                 SDL_CloseAudioDevice(deviceId);
                 SDL_FreeWAV(wavBuffer);
                return -1;
            }

            switch (e.type)
            {
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_RIGHT:
                        {
                            menuIdx = (menuIdx + 1) % 3;
                            //std::cout << "up " << menuIdx << std::endl;
                            stateChanged=true;
                            break;
                        }
                        case SDLK_LEFT:
                        {
                            menuIdx = (3 + menuIdx - 1) % 3;
                            //std::cout << "down " << menuIdx << std::endl;
                            stateChanged=true;
                            break;
                        }
                        case SDLK_ESCAPE:
                        {
                            SDL_CloseAudioDevice(deviceId);
                            SDL_FreeWAV(wavBuffer);
                            return -1;
                        }
                        case SDLK_RETURN:
                        {
                            SDL_CloseAudioDevice(deviceId);
                            SDL_FreeWAV(wavBuffer);
                            return menuIdx;
                        }

                        default:
                            break;
                    }
            }
            clearGl();
            screen.render();
            windowManager.swapBuffers();
            printErrors();

        }

    }

}
/**
 * pauseMenu()
 *
 * @return
 */
int Application::pauseMenu(){

    int i;
    int srfIdx=0;
    int loop1 = 1;
    int menuIdx = 0;


    //show the image cube with initial image
    std::vector<glcustom::Texture *> textures;
    RenderScreen screen = RenderScreen(programManager->getTexture2DProgram(), textures);

    std::string qualifier = "menuPause";
    screen.setTexture(textureManager->getRandomTexture(qualifier+std::to_string(1)));

    bool stateChanged=false;
    while (loop1)
    {

        //Update Screen
        //update texture from table
        if(stateChanged){
            screen.setTexture(textureManager->getRandomTexture(qualifier+std::to_string(menuIdx+1)));
            stateChanged= false;
        }

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                return QUIT;
            }

            switch (e.type)
            {
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_DOWN:
                        {
                            menuIdx = (menuIdx + 1) % 4;
                            //std::cout << "up " << menuIdx << std::endl;
                            stateChanged=true;
                            break;
                        }
                        case SDLK_UP:
                        {
                            menuIdx = (4 + menuIdx - 1) % 4;
                            //std::cout << "down " << menuIdx << std::endl;
                            stateChanged=true;
                            break;
                        }
                        case SDLK_ESCAPE:
                        {
                            return CONTINUE;
                        }
                        case SDLK_SPACE:
                        {
                            return CONTINUE;
                        }
                        case SDLK_RETURN:
                        {
                           if(menuIdx == 0) //continue
                               return CONTINUE;
                            else if (menuIdx == 1) //load
                           {
                               return CONTINUE;
                           }
                            else if(menuIdx == 2)  //save
                           {
                               return CONTINUE;
                           }
                            else if(menuIdx == 3) //mainMenu
                           {
                               return MAINMENU;
                           }
                        }

                        default:
                            break;
                    }
            }
            clearGl();
            screen.render();
            windowManager.swapBuffers();
            printErrors();

        }

    }

}
/**
 * start()
 * Ask the user to input something to generate a seed, and set it in the noiseManager
 */
int Application::start(){
    int choice = mainMenu(); //plus tard ça renverra le nom entré par l'user
    //pour les besoins de la soutenance, on charge une save. Plus tard, il suffira de set la seed avec un setSeed(name)


    /**a supprimer plus tard**/
    std::string initFileName;
    if (choice == 0) {
       initFileName = "712.txt";
    }
    else if (choice == 1){
       initFileName = "304.txt";
    }
    else if (choice == 2){
        initFileName = "771.txt";
    }
    else if (choice == -1)
        return choice;

    try {
        load(Tools::appPath+"data/"+initFileName);
    }catch (std::runtime_error e){
        throw e;
    }
    /***********************/

    return EXIT_SUCCESS;
}

/**
 * Final Application Loop
 * Handles initialization, SDL event loop and Rendering loop
 */
int Application::appLoop() {
    /**GPU PROGRAM**/
    programManager->createPrograms(); //must come before because menus uses gpu program to render

    /**
     * MAIN MENU
     */
    if(start() == -1) //quit
       return QUIT;

    std::cout << "seed : " << NoiseManager::getInstance().getSeed() << std::endl;

    /**
     * APP INITIALISATION
     */

    /**FBO**/
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

    glcustom::FBO fbo;

    /**ELEMENTS**/
    ElementManager::getInstance().createAllElements();

    /**LIGHTS**/
    int NIGHT = -1, DAY = 1, lightState =0;
    float lightAngle = 0;
    Light sun = Light(1,"Sun",glm::vec3(0.5,0.1,0));
    sun.addLightUniforms(programManager->getMapProgram());
    sun.addLightUniforms(programManager->getElementProgram());
    Light moon = Light(1,"Moon",glm::vec3(0,0.1,0.5));
    moon.addLightUniforms(programManager->getMapProgram());
    moon.addLightUniforms(programManager->getElementProgram());

    /**MAP**/
    ProceduralMap * Map = new ProceduralMap();
    Map->createRenderObject(programManager, textureManager);

    /**SKYBOX**/
    SkyboxObject * sky = new SkyboxObject();
    sky -> createRenderObject(programManager, textureManager);

    /**
     * SOUND
     */

    int soundRandom = (unsigned int)(NoiseManager::getInstance().getRandomFloat()*50)%6;
    std::string soundFile = "sounds/"+std::to_string(soundRandom)+".wav";
    std::cout << soundFile << std::endl;
    // load WAV file

    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;

    SDL_LoadWAV(soundFile.c_str (), &wavSpec, &wavBuffer, &wavLength);

    // open audio device
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    // play audio
    int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);

    /**
     * APP LOOP
     */

    bool done = false;
    int rightPressed = 0;
    bool multisamp= false;
    camera->moveFront(Tools::speed);

    bool rotatebutton = false;
    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;

    bool rotateLeft = false;
    bool rotateRight = false;
    bool rotateUp = false;
    bool rotateDown = false;


    // Application loop:
    //bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_z  && e.key.state == SDL_PRESSED) { // Z
                    moveUp = true;
                } else if (e.key.keysym.sym == SDLK_s  && e.key.state == SDL_PRESSED) { // S
                    moveDown = true;
                }
                if (e.key.keysym.sym == SDLK_q && e.key.state == SDL_PRESSED) { // Q
                    moveLeft = true;
                } else if (e.key.keysym.sym == SDLK_d  && e.key.state == SDL_PRESSED) { // D
                    moveRight = true;
                }
                if (e.key.keysym.sym == SDLK_UP  && e.key.state == SDL_PRESSED) {
                    rotateUp = true;
                } else if (e.key.keysym.sym == SDLK_DOWN  && e.key.state == SDL_PRESSED) {
                    rotateDown = true;
                }
                if (e.key.keysym.sym == SDLK_RIGHT && e.key.state == SDL_PRESSED) {
                    rotateLeft = true;
                } else if (e.key.keysym.sym == SDLK_LEFT  && e.key.state == SDL_PRESSED) {
                    rotateRight = true;
                }
                if (e.key.keysym.sym == SDLK_v) {
                    if (camera->getChoice() == 0) {
                        camera->setChoice(1);
                    } else {
                        //camera->setChoice(0);
                    }
                } else if (e.key.keysym.sym == SDLK_b) {
                    programManager->reloadPrograms();
                }
                else if (e.key.keysym.sym == SDLK_m) {
                    multisamp = !multisamp;
                }
                if(e.key.keysym.sym == SDLK_SPACE){ //pause
                    //stop sound
                    SDL_PauseAudioDevice(deviceId, 1);
                    //pauseMenu
                    int choice = pauseMenu();
                    if(choice == QUIT || choice == MAINMENU) {//quit
                        delete sky;
                        delete Map;
                        SDL_CloseAudioDevice(deviceId);
                        SDL_FreeWAV(wavBuffer);
                        return choice;
                    }
                    //continue game
                    SDL_PauseAudioDevice(deviceId, 0);

                }
            }
            if(e.type == SDL_KEYUP){
                if (e.key.keysym.sym == SDLK_z  && e.key.state == SDL_RELEASED) { // Z
                    moveUp = false;
                } else if (e.key.keysym.sym == SDLK_s  && e.key.state == SDL_RELEASED) { // S
                    moveDown = false;
                }
                if (e.key.keysym.sym == SDLK_q && e.key.state == SDL_RELEASED) { // Q
                    moveLeft = false;
                } else if (e.key.keysym.sym == SDLK_d  && e.key.state == SDL_RELEASED) { // D
                    moveRight = false;
                }
                if (e.key.keysym.sym == SDLK_UP  && e.key.state == SDL_RELEASED) { // Z
                    rotateUp = false;
                } else if (e.key.keysym.sym == SDLK_DOWN  && e.key.state == SDL_RELEASED) { // S
                    rotateDown = false;
                }
                if (e.key.keysym.sym == SDLK_RIGHT && e.key.state == SDL_RELEASED) { // Q
                    rotateLeft = false;
                } else if (e.key.keysym.sym == SDLK_LEFT  && e.key.state == SDL_RELEASED) { // D
                    rotateRight = false;
                }
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_RIGHT) {
                    rightPressed = 1;
                }
            }
            else if (e.type == SDL_MOUSEBUTTONUP) {
                if (e.button.button == SDL_BUTTON_RIGHT) {
                    rightPressed = 0;
                }
            } else if (e.type == SDL_MOUSEMOTION && rightPressed == 1) {
                camera->rotateLeft(e.motion.xrel);
                camera->rotateUp(e.motion.yrel);
            }
            if(e.type == SDL_QUIT) {
                delete sky;
                delete Map;
                SDL_CloseAudioDevice(deviceId);
                SDL_FreeWAV(wavBuffer);
                return QUIT;
            }
            if(e.type == SDL_MOUSEBUTTONDOWN && e.wheel.y == 1){
                camera->zoom(-Tools::speed);
            }
            if(e.type == SDL_MOUSEBUTTONDOWN && e.wheel.y == -1){
                camera->zoom(Tools::speed);
            }
            if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT){
                rotatebutton = true;
            }
            if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT){
                rotatebutton = false;
            }
            if(e.type == SDL_MOUSEMOTION && rotatebutton){

            }
        }

        if(moveLeft == true){
            camera->moveLeft(Tools::speed);
        }
        if(moveRight == true){
            camera->moveLeft(-Tools::speed);
        }
        if(moveUp == true){
            camera->moveFront(Tools::speed);
        }
        if(moveDown == true){
            camera->moveFront(-Tools::speed);
        }
        if(rotateLeft == true){
            camera->rotateLeft(Tools::speed/4);
        }
        if(rotateRight == true){
            camera->rotateLeft(-Tools::speed/4);
        }
        if(rotateUp == true){
            camera->rotateUp(-Tools::speed/4);
        }
        if(rotateDown == true){
            camera->rotateUp(Tools::speed/4);
        }




        fbo.bind();
        //glcustom::Texture lightDepth = fbo.attachDepthTexture(Tools::windowWidth, Tools::windowHeight);
        //textureManager->addTexture(&lightDepth,"shadowMap");
        glcustom::Texture beauty = fbo.attachColorTexture(Tools::windowWidth, Tools::windowHeight);
        glcustom::Texture depth = fbo.attachDepthTexture(Tools::windowWidth, Tools::windowHeight);
        fbo.checkComplete();
        clearGl();


        /**************LIGHT DEPTH BUFFER***********/
        /*
        depthViewMatrix = glm::lookAt(glm::vec3(sun.getDirection().x,sun.getDirection().y,sun.getDirection().z),
                                                glm::vec3(0,0,0),
                                                glm::vec3(0,1,0));
        depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;
        depthBiasMVP = biasMatrix*depthMVP;
        */
        //configuring and sending light uniforms
        programManager->getMapProgram()->use();
        programManager->getMapProgram()->sendUniformMat4("uDepthMVP",depthBiasMVP);


        lightAngle = (windowManager.getTime()+lightRotation)*0.4;

        sun.resetDirection(DAY);
        sun.rotate(lightAngle, camera->getViewMatrix());
        sun.sendLightUniforms(programManager->getMapProgram());

        if(sun.getDirection().y < 0) {
            lightState = NIGHT;
            //std::cout <<"night"<<std::endl;
        }
        else{
            lightState = DAY;
            //std::cout <<"day"<<std::endl;

        }

        moon.resetDirection(NIGHT);
        moon.rotate(lightAngle, camera->getViewMatrix());
        moon.sendLightUniforms(programManager->getMapProgram());

        programManager->getElementProgram()->use();
        programManager->getElementProgram()->sendUniformMat4("uDepthMVP",depthBiasMVP);
        sun.sendLightUniforms(programManager->getElementProgram());
        moon.sendLightUniforms(programManager->getElementProgram());

        //render the map with light point of view
        //Map->draw(depthBiasMVP);
        //fbo.debind();

        //fbo.attachDepthTexture(Tools::windowWidth, Tools::windowHeight);

        /***************MAP FRAME BUFFER****************/
        //draw skybox
        glDepthMask(GL_FALSE);
        sky->draw(camera->getViewMatrix());
        glDepthMask(GL_TRUE);
        //draw map
        Map->draw(camera->getViewMatrix());


        /**************BLUR****************************/
        glm::vec4 dir = sun.getDirection();
        glm::vec3 color = lightState==-1?moon.getColor():sun.getColor();
        if(multisamp){
            std::cout << "multisample on" << std::endl;
            glEnable(GL_MULTISAMPLE);
        }

        addDOF(&beauty, &depth, fbo, color, dir);
        if (multisamp) {
            glDisable(GL_MULTISAMPLE);
        }

        /********************************************/
        windowManager.swapBuffers();
        printErrors();

    }

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
 const glimac::SDLWindowManager &Application::getWindowManager() const  {
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

    ProceduralObject * rock = ElementManager::getInstance().createProceduralFeuillage();
    rock->addInstance(glm::vec3(0,0,0), Color(1,1,0));
    rock->createRenderObject(programManager, textureManager);

    /*glcustom::FBO fbo;
    fbo.bind();
    glcustom::Texture originalColor = fbo.attachColorTexture(Tools::windowWidth, Tools::windowHeight);
    glcustom::Texture originalDepth = fbo.attachDepthTexture(Tools::windowWidth, Tools::windowHeight);
    fbo.checkComplete();*/


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
        sun.resetDirection(1);
        sun.rotate(windowManager.getTime(), camera->getViewMatrix());
        sun.sendLightUniforms(programManager->getMapProgram());

        moon.resetDirection(-1);
        moon.rotate(windowManager.getTime(), camera->getViewMatrix());
        moon.sendLightUniforms(programManager->getMapProgram());

        programManager->getElementProgram()->use();
        sun.sendLightUniforms(programManager->getElementProgram());
        moon.sendLightUniforms(programManager->getElementProgram());


        /******
        Example : testObject->draw(camera->getViewMatrix());
         ******/


        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        std::vector<ProceduralObject *> elements = ElementManager::getInstance().getAllElements();
        for (ProceduralObject * el : elements){
            el->draw(camera->getViewMatrix());
        }
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
        //addDOF(&originalColor, &originalDepth, fbo);

        windowManager.swapBuffers();
        printErrors();

        //glDeleteFramebuffers(1, &frameBuffer);

    }
    delete test;


}

void Application::addDOF(glcustom::Texture *beauty, glcustom::Texture *depth, glcustom::FBO &fbo, glm::vec3 &lightColor, glm::vec4 &lightDir) {

    /* TEST MULTISAMPLING
    int num_samples = 4;
    GLuint tex, fboMSAA;
    glGenTextures( 1, &tex );
    glBindTexture( GL_TEXTURE_2D_MULTISAMPLE, tex );
    glTexImage2DMultisample( GL_TEXTURE_2D_MULTISAMPLE, num_samples, GL_RGBA8, Tools::windowWidth, Tools::windowHeight, false );

    glGenFramebuffers( 1, &fboMSAA );
    glBindFramebuffer( GL_FRAMEBUFFER, fboMSAA );
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, tex, 0 );

    GLenum status = glCheckFramebufferStatus( GL_FRAMEBUFFER );
    glClear(GL_COLOR_BUFFER_BIT);

    fbo.bind();
    /*END TEST*/

    //glcustom::Texture initialDepth = *depth;
    // std::vector<glcustom::Texture *> texts = { beauty, depth};

    glcustom::Texture blur = fbo.attachColorTexture(Tools::windowWidth, Tools::windowHeight);
    fbo.attachDepthTexture(Tools::windowWidth, Tools::windowHeight);

    //pass couleur
    std::vector<glcustom::Texture *> texts = { beauty, depth };
    RenderScreen screenColorCorrec(programManager->getGammaProgram(), texts);
    programManager->getGammaProgram()->use();
    programManager->getGammaProgram()->sendUniformVec3("uLightColor",lightColor);
    programManager->getGammaProgram()->sendUniformVec4("uLightDir",lightDir);
    screenColorCorrec.render(&fbo);


    texts.clear();
    texts.push_back(&blur);
//blur horizontal
    RenderScreen screenBlur(programManager->getBlurProgram(), texts);
    programManager->getBlurProgram()->use();
    programManager->getBlurProgram()->sendUniform1i("uSampleCount", 2);
    programManager->getBlurProgram()->sendUniformVec3("uDirection", glm::vec3(0,1,0));
    screenBlur.render(&fbo);

//blur vertical
    programManager->getBlurProgram()->sendUniformVec3("uDirection", glm::vec3(1,0,0));
    screenBlur.render(&fbo);

//rend avec DOF
    texts.push_back(beauty);
    texts.push_back(depth);
    RenderScreen screenDOF(programManager->getDOFProgram(), texts);
    screenDOF.render();

    /*SUITE TEST MSAA
    screenDOF.render(fboMSAA);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);   // Make sure no FBO is set as the draw framebuffer
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fboMSAA); // Make sure your multisampled FBO is the read framebuffer
    glDrawBuffer(GL_BACK);                       // Set the back buffer as the draw buffer
    glBlitFramebuffer(0, 0, Tools::windowWidth, Tools::windowHeight, 0, 0, Tools::windowWidth, Tools::windowHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    /*FIN TEST*/




}
void Application::play(glimac::FilePath f){
    int done = CONTINUE;
    Application *app = nullptr;
    while(done != QUIT){
        app = new Application(f);
        done = app->appLoop();
        delete app;
        std::cout <<"delete app ok" << std::endl;
        app = nullptr;
    }
}