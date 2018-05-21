//
// Created by natshez on 02/04/2018.
//

#include "MenuManager.hpp"

/**
 * saveMenu()
 * TextHandler allows to input/output specific texts.
 * This function is used to ask the user to choose an existing save and set the choosen world
 * @return int among the enum defined in Tool class, represents the action of the user
 */
int MenuManager::saveMenu(){
    int choosenSave=0;
    SaveHandler * handler = new SaveHandler(app->getWindowManager().getWindow());
    int res = handler->handle(&choosenSave); //ask the user to choose a save
    delete(handler);
    if (res == SAVE){
        try {
            app->save(choosenSave); //set the world from save content
        }catch (std::runtime_error e){
            throw e;
        }
        return PLAY;
    }
    else
        return PAUSE;
}
/**
 * seedInputMenu()
 * TextHandler allows to input/output specific texts.
 * This function is used to ask user's name
 * @param inputText represents the user's name
 * @return int among the enum defined in Tool class, represents the button clicked in the menu
 */
int MenuManager::seedInputMenu(std::string *inputText){
    TextHandler * handler = new TextHandler(app->getWindowManager().getWindow());
    int res = handler->handle(inputText);
    if(res == PLAY)
        NoiseManager::getInstance().setSeed(*inputText);
    delete(handler);
    return res;
}
/**
 * loadMenu()
 * TextHandler allows to input/output specific texts.
 * This function is used to ask the user to choose an existing save and set the choosen world
 * @return int among the enum defined in Tool class, represents the action of the user
 */
int MenuManager::loadMenu(){
    std::string loadName="";
    LoadHandler * handler = new LoadHandler(app->getWindowManager().getWindow());
    int res = handler->handle(&loadName); //ask the user to choose a save
    delete(handler);
    if (res == LOAD){
        try {
            app->load(loadName); //set the world from save content
        }catch (std::runtime_error e){
            throw e;
        }
        return PLAY;
    }
    else
        return res; //back to main menu or quit
}

/**
 * MainMenu()
 * @param inputText represents the user's name
 * @return int among the enum defined in Tool class, represents the button clicked in the menu
 */
int MenuManager::mainMenu(std::string *inputText){

    int i;
    int srfIdx=0;
    int menuIdx = 0;
    int quit = MAINMENU;

    //show the image cube with initial image
    std::vector<glcustom::Texture *> textures;
    RenderScreen screen = RenderScreen(app->getProgramManager()->getTexture2DProgram(), textures);

    std::string qualifier = "menuHome";
    screen.setTexture(app->getTextureManager()->getRandomTexture(qualifier+std::to_string(1)));

    bool stateChanged=false;
    while (quit == MAINMENU)
    {

        //Update Screen
        //update texture from table
        if(stateChanged){
            screen.setTexture(app->getTextureManager()->getRandomTexture(qualifier+std::to_string(menuIdx+1)));
            stateChanged= false;
        }

        SDL_Event e;
        while (SDL_PollEvent(&e) && quit == MAINMENU)
        {
            if (e.type == SDL_QUIT)
            {
                quit = QUIT;
            }

            switch (e.type)
            {
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_RIGHT:
                        {
                            menuIdx = (menuIdx + 1) % 3;
                            stateChanged=true;
                            break;
                        }
                        case SDLK_LEFT:
                        {
                            menuIdx = (3 + menuIdx - 1) % 3;
                            stateChanged=true;
                            break;
                        }
                        case SDLK_ESCAPE:
                        {
                            quit = QUIT;
                            break;
                        }
                        case SDLK_RETURN:
                        {
                            if(menuIdx == 0) //new world
                            {
                                quit =seedInputMenu(inputText);
                            }
                            else if (menuIdx == 1) //load internly a world
                            {
                                quit = loadMenu(); //screen for choosing a save
                            }
                            else if(menuIdx == 2)  //exit
                            {
                                quit =  QUIT;
                            }
                            break;
                        }

                        default:
                            break;
                    }
            }
            app->clearGl();
            screen.render();
            app->swapSDLBuffers();
            app->printErrors();

        }
    }
    return quit;
}
/**
 * pauseMenu()
 *
 * @return
 */
int MenuManager::pauseMenu(){

    int i;
    int srfIdx=0;
    int quit = PAUSE;
    int menuIdx = 0;


    //show the image cube with initial image
    std::vector<glcustom::Texture *> textures;
    RenderScreen screen = RenderScreen(app->getProgramManager()->getTexture2DProgram(), textures);

    std::string qualifier = "menuPause";
    screen.setTexture(app->getTextureManager()->getRandomTexture(qualifier+std::to_string(1)));

    bool stateChanged=false;
    while (quit == PAUSE)
    {

        //Update Screen
        //update texture from table
        if(stateChanged){
            screen.setTexture(app->getTextureManager()->getRandomTexture(qualifier+std::to_string(menuIdx+1)));
            stateChanged= false;
        }

        SDL_Event e;
        while (SDL_PollEvent(&e) & quit == PAUSE)
        {
            if (e.type == SDL_QUIT)
                quit = QUIT;

            switch (e.type)
            {
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_DOWN:
                        {
                            menuIdx = (menuIdx + 1) % 4;
                            stateChanged=true;
                            break;
                        }
                        case SDLK_UP:
                        {
                            menuIdx = (4 + menuIdx - 1) % 4;
                            stateChanged=true;
                            break;
                        }
                        case SDLK_ESCAPE:
                        {
                            quit = QUIT;
                            break;
                        }
                        case SDLK_SPACE:
                        {
                            quit = PLAY;
                            break;
                        }
                        case SDLK_RETURN:
                        {
                            if(menuIdx == 0) //continue
                                quit = PLAY;
                            else if (menuIdx == 1) //quit
                            {
                                quit = QUIT;
                            }
                            else if(menuIdx == 2)  //save
                            {
                                quit = saveMenu();
                            }
                            else if(menuIdx == 3) //mainMenu
                            {
                                quit = MAINMENU;
                            }
                            break;
                        }

                        default:
                            break;
                    }
            }
            app->clearGl();
            screen.render();
            app->swapSDLBuffers();
            app->printErrors();
        }

    }
    return quit;

}
