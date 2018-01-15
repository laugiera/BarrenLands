//
// Created by Lou Landry on 15/01/2018.
//

#ifndef BARRENLANDS_APPLICATION_HPP
#define BARRENLANDS_APPLICATION_HPP

#define GLEW_STATIC
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "glimac/SDL2WindowManager.hpp"
#include "Tools.hpp"

class Application {
public:
    Application();
    void initOpenGl();
    void clearGl();
    void appLoop();

private:
    glimac::SDLWindowManager windowManager;
};


#endif //BARRENLANDS_APPLICATION_HPP
