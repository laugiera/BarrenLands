//
// Created by natshez on 02/04/2018.
//

#ifndef BARRENLANDS_MENUMANAGER_H
#define BARRENLANDS_MENUMANAGER_H

#define GLEW_STATIC
#include <iostream>
#include "glimac/FilePath.hpp"
#include <TextHandler.hpp>
#include <LoadHandler.hpp>
#include <SaveHandler.hpp>
#include <Application.hpp>

/**
 * class MenuManager handles main, pause, save, load and create menus
 */

class Application;

class MenuManager {

private :
    Application * app;

public:
    MenuManager(Application * _app){
        this->app = _app;
    }
    ~MenuManager(){
        this->app = nullptr;
    }
    int  mainMenu(std::string *inputText);
    int pauseMenu();
    int seedInputMenu(std::string *inputText);
    int loadMenu();
    int saveMenu();

};


#endif //BARRENLANDS_MENUMANAGER_H
